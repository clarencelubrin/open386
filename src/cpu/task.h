/*
 * open386 — task state segments and hardware task switching.
 *
 * Ref: [i386 §7.1 p.130-132, Fig 7-1 32-bit TSS]; [i386 §7.2 p.133 Fig 7-2 TSS descriptor]; [i386 §7.3 p.134 TR];
 *      [i386 §7.4 p.135 Fig 7-4 task gate]; [i386 §7.5 p.137-140 switch steps]; [i386 §7.6 p.141 busy bit, NT];
 *      [i386 §9.8.10 p.165 #TS conditions]; [SDM 3A §10.2.1 Fig 10-2; §10.3 p.3451 Tables 10-1/10-2;
 *       §10.4 p.3457 linking; §10.6 p.3460 Fig 10-10 16-bit TSS].
 * ICS-OS: ltr + `jmp TSS:0` (kernel/startup/asmlib.asm:548-563), task gates for IRQ0 and #PF
 * (kernel/hardware/chips/irqhandlers.c:258,369,413).
 */
#ifndef open386_CPU_TASK_H
#define open386_CPU_TASK_H

#include "types.h"
#include "cpu/segment.h"

/* Byte offsets inside a 32-bit TSS. [i386 Fig 7-1 p.131; SDM 3A Fig 10-2 p.3446] */
enum tss32_offset {
    TSS32_BACKLINK = 0,
    TSS32_ESP0 = 4,  TSS32_SS0 = 8,
    TSS32_ESP1 = 12, TSS32_SS1 = 16,
    TSS32_ESP2 = 20, TSS32_SS2 = 24,
    TSS32_CR3 = 28,
    TSS32_EIP = 32,
    TSS32_EFLAGS = 36,
    TSS32_EAX = 40, TSS32_ECX = 44, TSS32_EDX = 48, TSS32_EBX = 52,
    TSS32_ESP = 56, TSS32_EBP = 60, TSS32_ESI = 64, TSS32_EDI = 68,
    TSS32_ES = 72, TSS32_CS = 76, TSS32_SS = 80, TSS32_DS = 84, TSS32_FS = 88, TSS32_GS = 92,
    TSS32_LDT = 96,
    TSS32_TRAP = 100,      /* bit 0 = T (debug trap on task switch) [i386 §12.3.1.5 p.203] */
    TSS32_IOMAP_BASE = 102,
    TSS32_SIZE = 104,
    TSS32_MIN_LIMIT = 103  /* limit < 103 → #TS [i386 §9.8.10 p.165] */
};

/* Byte offsets inside a 16-bit (80286) TSS. [SDM 3A Fig 10-10 p.3460] */
enum tss16_offset {
    TSS16_BACKLINK = 0,
    TSS16_SP0 = 2, TSS16_SS0 = 4,
    TSS16_SP1 = 6, TSS16_SS1 = 8,
    TSS16_SP2 = 10, TSS16_SS2 = 12,
    TSS16_IP = 14, TSS16_FLAGS = 16,
    TSS16_AX = 18, TSS16_CX = 20, TSS16_DX = 22, TSS16_BX = 24,
    TSS16_SP = 26, TSS16_BP = 28, TSS16_SI = 30, TSS16_DI = 32,
    TSS16_ES = 34, TSS16_CS = 36, TSS16_SS = 38, TSS16_DS = 40,
    TSS16_LDT = 42,
    TSS16_SIZE = 44,
    TSS16_MIN_LIMIT = 43
};

/* In-memory image of the 32-bit TSS (little-endian, packed by construction: all fields naturally aligned). */
struct tss32 {
    u16 back_link, rsvd0;
    u32 esp0; u16 ss0, rsvd1;
    u32 esp1; u16 ss1, rsvd2;
    u32 esp2; u16 ss2, rsvd3;
    u32 cr3;
    u32 eip;
    u32 eflags;
    u32 eax, ecx, edx, ebx, esp, ebp, esi, edi;
    u16 es, rsvd4, cs, rsvd5, ss, rsvd6, ds, rsvd7, fs, rsvd8, gs, rsvd9;
    u16 ldt, rsvd10;
    u16 trap;        /* bit 0 = T */
    u16 iomap_base;  /* offset of the I/O permission bit map [i386 §8.3.2 p.149] */
};

struct tss16 {
    u16 back_link;
    u16 sp0, ss0, sp1, ss1, sp2, ss2;
    u16 ip, flags;
    u16 ax, cx, dx, bx, sp, bp, si, di;
    u16 es, cs, ss, ds;
    u16 ldt;
};

/* What triggered the switch — decides privilege checks and busy/NT/back-link handling. [SDM 3A Table 10-2] */
enum task_switch_reason {
    TASK_SWITCH_JMP = 0,  /* old TSS → available, no link */
    TASK_SWITCH_CALL,     /* old stays busy, NT=1, back link = old TR */
    TASK_SWITCH_INT,      /* interrupt/exception through a task gate: like CALL */
    TASK_SWITCH_IRET      /* NT=1 return: old → available, new must be busy */
};

struct cpu;

/* Perform a complete task switch to `new_tss_selector` whose descriptor the caller fetched.
 * Implements the numbered steps of [i386 §7.5 p.138-140] and the checks of [SDM 3A Table 10-1]. The
 * optional error code is pushed on the new task's stack for #PF/#GP/… through task gates [i386 §9.7 p.161]. */
void task_switch(struct cpu *cpu, u16 new_tss_selector, const struct segment_descriptor *new_tss_desc,
                 u32 new_tss_desc_addr, enum task_switch_reason reason, bool has_error_code, u32 error_code);
/* Validate the new task's segment selectors in architectural order after the state load. */
void task_validate_segments(struct cpu *cpu, const struct tss32 *tss);
/* Read SSn:ESPn for an inter-level transfer. #TS(TR selector) when outside the TSS limit. [i386 Fig 6-8 p.120] */
void task_get_privileged_stack(struct cpu *cpu, u8 privilege, u16 *ss_out, u32 *esp_out);
/* I/O permission bit map check for `size` consecutive ports. [i386 §8.3.2 p.149-151; SDM 1 §20.5.2 p.438] */
bool task_io_permitted(struct cpu *cpu, u16 port, u8 size);
void task_save_state(struct cpu *cpu, u32 tss_base, bool is_32bit);
void task_load_state(struct cpu *cpu, u32 tss_base, bool is_32bit);
bool task_tss_is_32bit(const struct segment_descriptor *tss_desc);
void task_read_tss32(struct cpu *cpu, u32 tss_base, struct tss32 *out);
void task_write_tss32(struct cpu *cpu, u32 tss_base, const struct tss32 *in);

#endif /* open386_CPU_TASK_H */
