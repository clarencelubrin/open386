/********************************************* CPU *********************************************
 * @file cpu.h
 * @author Lubrin, Clarence, U.
 * @details The 80386 processor model: architectural state and the step API.
 *
 * @cite [i386 Ch.2 p.22-44 basic programming model]; [i386 Ch.4 p.85-90 system registers];
 *      [i386 §5.1.4 p.97, Fig 5-7] segment registers with cached descriptor ("hidden part");
 *      [i386 Ch.10 p.174-175 reset state]; [i386 §9.2-9.3 p.153-155 interrupt masking and priority];
 *      [SDM 3A §2.2 p.3213, Fig 2-3 mode transitions; §12.1 Table 12-1 p.3522].
 */
#ifndef open386_CPU_CPU_H
#define open386_CPU_CPU_H

#include <setjmp.h>
#include <stdio.h>
#include "types.h"
#include "cpu/regs.h"
#include "cpu/flags.h"
#include "cpu/features.h"
#include "cpu/decode.h"
#include "cpu/paging.h"
#include "cpu/interrupt.h"
#include "cpu/debugregs.h"
#include "cpu/fpu.h"

/* Operating mode, derived from CR0.PE and EFLAGS.VM. [i386 §14.4 p.209; §15.3 p.221; SDM 3A Fig 2-3] */
enum cpu_mode {
    CPU_MODE_REAL = 0,
    CPU_MODE_PROTECTED,
    CPU_MODE_V8086
};

/* CR0 bits. [i386 §4.1.3 p.87-88, Fig 4-2]; 486/Pentium bits per [SDM 3B §25.21 p.4140]. */
#define CR0_PE (1u << 0)
#define CR0_MP (1u << 1)
#define CR0_EM (1u << 2)
#define CR0_TS (1u << 3)
#define CR0_ET (1u << 4)  /* 387 present; read-only on later CPUs */
#define CR0_NE (1u << 5)  /* Intel486 */
#define CR0_WP (1u << 16) /* Intel486 */
#define CR0_AM (1u << 18) /* Intel486 */
#define CR0_NW (1u << 29) /* Intel486 */
#define CR0_CD (1u << 30) /* Intel486 */
#define CR0_PG (1u << 31)
#define CR0_I386_WRITABLE (CR0_PE | CR0_MP | CR0_EM | CR0_TS | CR0_PG)
#define CR0_MSW_MASK      (CR0_PE | CR0_MP | CR0_EM | CR0_TS) /* LMSW/SMSW operate on the low word; LMSW cannot clear PE */

/* CR4 bits (Pentium+, gated by CPUF_CR4). [SDM 3B §25.21 p.4140; SDM 3A §2.5 Fig 2-7] */
#define CR4_VME (1u << 0)
#define CR4_PVI (1u << 1)
#define CR4_TSD (1u << 2)
#define CR4_DE  (1u << 3)
#define CR4_PSE (1u << 4)
#define CR4_PAE (1u << 5)
#define CR4_MCE (1u << 6)
#define CR4_PGE (1u << 7)
#define CR4_PCE (1u << 8)
#define CR4_OSFXSR (1u << 9)
#define CR4_OSXMMEXCPT (1u << 10)

/* Reset vector. [i386 §10.1 p.174; §14.8.2 p.216; SDM 3A §12.1.4 p.3525] */
#define CPU_RESET_EIP        0x0000FFF0u
#define CPU_RESET_CS_SEL     0xF000u
#define CPU_RESET_CS_BASE    0xFFFF0000u
#define CPU_RESET_IDTR_LIMIT 0x03FFu
#define CPU_RESET_DESC_LIMIT 0xFFFFu
#define CPU_I386_COMPONENT_ID 0x03u /* DH after reset [i386 Fig 10-1 p.175] */

/* Cached ("hidden") part of a segment register plus its visible selector. [i386 Fig 5-7 p.97] */
typedef struct seg_cache {
    u16  selector;
    u32  base;
    u32  limit;        // byte-granular (already expanded for G=1)
    u8   type;         // 4-bit descriptor type
    bool s;            // code/data vs system
    u8   dpl;
    bool present;
    bool db;           // D/B: default operand/address size (CS), stack pointer size (SS)
    bool granularity;
    bool avl;
    bool valid;        // false after loading a null selector into DS/ES/FS/GS
} SegCache;

typedef struct desc_table_reg {
    u32 base;
    u16 limit;
} DescTableReg;

/* Callbacks the machine installs so the CPU never includes device headers. */
typedef struct cpu_hooks {
    void *ctx;
    u8   (*intr_ack)(void *ctx);                       // interrupt-acknowledge cycle → vector from the 8259A
    void (*halt)(void *ctx);                           // HLT entered
    void (*shutdown)(void *ctx);                       // triple fault / shutdown cycle
    bool (*code_fetch_hook)(void *ctx, u32 phys_eip);  // HLE BIOS entry-point trap (PLAN.md §6.3)
} CPUHooks;

typedef struct memory PhysicalMemory;
typedef struct iobus IOBus;

typedef struct cpu {
    const CPUModel *model;
    CPUModel model_storage;  // when overrides were applied

    /* Application-visible state. */
    u32 gpr[REG_GPR_COUNT];          // general purpose registers
    u32 eip;
    u32 eflags;                      // status flags may be stale while lazy.op != FLAGOP_NONE
    LazyFlags lazy;
    SegCache seg[SEG_COUNT];

    /* System state. [i386 Ch.4] */
    DescTableReg gdtr;
    DescTableReg idtr;
    SegCache ldtr;           // selector + cached LDT descriptor
    SegCache tr;             // selector + cached TSS descriptor
    u32 cr[CREG_COUNT];              // control registers
    u32 dr[DREG_COUNT];
    u32 tr6, tr7;                    // TLB test registers [i386 §10.6]
    X87State fpu;
    TLB tlb;
    DebugState dbg;

    /* Derived / execution state. */
    enum cpu_mode mode;
    u8   cpl;
    bool halted;
    bool shutdown;

    bool intr_line;                  // INTR pin level
    bool nmi_pending;
    bool nmi_masked;                 // set on NMI delivery until IRET [i386 §9.2.1 p.154]
    u8   inhibit_interrupts;         // one-instruction shadow after MOV/POP SS and STI [i386 §9.2.4 p.154]
    X86Insn cur;                     // instruction being executed
    jmp_buf exc_jmp;                 // longjmp target for cpu_raise_exception()
    bool exc_jmp_valid;
    PendingException exc;            // Most recently raised exception (written by cpu_raise_exception)
    PendingException delivering;     // Event currently being delivered by cpu_dispatch_event
    u8   exc_in_progress;            // vector of the exception being delivered (for #DF decisions), or 0xFF
    u64  cycles;
    u64  insn_count;

    PhysicalMemory *mem;
    IOBus  *io;
    CPUHooks hooks;
    u32 trace_mask;
} CPU;

int cpu_init(CPU *cpu, const CPUModel *model, PhysicalMemory *mem, IOBus *io, const CPUHooks *hooks);
void cpu_reset(CPU *cpu);                      /* [i386 §10.1] + model-specific values */
/* Execute one instruction (or deliver one pending event). Returns cycles consumed. */
u32 cpu_step(CPU *cpu);
void cpu_set_intr(CPU *cpu, bool level);
void cpu_raise_nmi(CPU *cpu);
void cpu_update_mode(CPU *cpu);                /* recompute mode/CPL after CR0 or EFLAGS.VM change */
enum cpu_mode cpu_current_mode(const CPU *cpu);
u8 cpu_get_cpl(const CPU *cpu);
void cpu_set_cpl(CPU *cpu, u8 cpl);
bool cpu_is_user_mode(const CPU *cpu);         /* CPL == 3, for paging U/S checks */
u8 cpu_default_opsize(const CPU *cpu);         /* 2 or 4 from CS.D [i386 §17.1.1 p.239] */
u8 cpu_default_addrsize(const CPU *cpu);
u8 cpu_stack_addrsize(const CPU *cpu);         /* from SS.B [i386 §17.1.3 p.240] */
void cpu_write_cr0(CPU *cpu, u32 value);       /* mode switch, paging on/off, reserved-bit policy */
void cpu_write_cr3(CPU *cpu, u32 value);
void cpu_write_cr4(CPU *cpu, u32 value);
u32 cpu_read_cr(CPU *cpu, u8 n);
/* Register accessors by size, used by the executor. */
u32 cpu_get_reg(const CPU *cpu, u8 reg, u8 size);
void cpu_set_reg(CPU *cpu, u8 reg, u8 size, u32 value);
void cpu_dump_state(const CPU *cpu, FILE *out);
void cpu_dump_segment(const SegCache *sc, const char *name, FILE *out);

#endif /* open386_CPU_CPU_H */
