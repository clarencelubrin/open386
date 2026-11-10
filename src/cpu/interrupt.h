/*
 * open386 — exceptions, interrupts, IDT delivery and IRET.
 *
 * Ref: [i386 Ch.9 p.152-173: Table 9-1 vectors, §9.1 classes, §9.2 masking, §9.3 priority Table 9-2,
 *       §9.4-9.5 IDT Fig 9-1/9-2/9-3, §9.6 procedures/tasks Fig 9-4/9-5/9-6, §9.7 error code Fig 9-7,
 *       §9.8 conditions, §9.9 Table 9-6, §9.10 Table 9-7];
 *      [i386 §14.3 p.209 real mode; §15.3.2 p.223 V86 entry Fig 15-3];
 *      [SDM 3A Ch.7 p.3351-3411: Table 7-1, Table 7-2, §7.12 Fig 7-3/7-4/7-6, §7.13 Fig 7-7, Table 7-5, Table 7-6].
 */
#ifndef open386_CPU_INTERRUPT_H
#define open386_CPU_INTERRUPT_H

#include "types.h"
#include "cpu/segment.h"

/* Vector assignments. [i386 Table 9-1 p.153; SDM 3A Table 7-1 p.3351] */
enum x86_exception {
    EXC_DE = 0,          // divide error (fault)
    EXC_DB = 1,          // debug (fault or trap)
    EXC_NMI = 2,
    EXC_BP = 3,          // INT 3 (trap)
    EXC_OF = 4,          // INTO (trap)
    EXC_BR = 5,          // BOUND (fault)
    EXC_UD = 6,          // invalid opcode (fault)
    EXC_NM = 7,          // coprocessor not available (fault)
    EXC_DF = 8,          // double fault (abort), error code 0
    EXC_COPROC_SEG = 9,  // coprocessor segment overrun (abort) — 386/387 only
    EXC_TS = 10,         // invalid TSS (fault), error code
    EXC_NP = 11,         // segment not present (fault), error code
    EXC_SS = 12,         // stack fault (fault), error code
    EXC_GP = 13,         // general protection (fault), error code
    EXC_PF = 14,         // page fault (fault), error code + CR2
    EXC_RESERVED15 = 15,
    EXC_MF = 16,         // coprocessor error (fault)
    /* Post-386 (gated): */
    EXC_AC = 17,         // alignment check, Intel486
    EXC_MC = 18,         // machine check, Pentium
    EXC_XM = 19,         // SIMD FP, Pentium III
    EXC_VE = 20,
    EXC_CP = 21,
    EXC_FIRST_EXTERNAL = 32
};

enum exception_class {
    EXC_CLASS_FAULT = 0, // return address = faulting instruction
    EXC_CLASS_TRAP,      // return address = next instruction
    EXC_CLASS_ABORT      // not restartable
};

/* Origin of an event, which decides EXT bit, DPL checks and inhibit rules. [i386 §3.5.3 p.68; §9.7 p.161] */
enum event_source {
    EVENT_EXCEPTION = 0, // processor-detected
    EVENT_SOFTWARE_INT,  // INT n — gate DPL >= CPL check applies, EXT = 0
    EVENT_INT3,
    EVENT_INTO,
    EVENT_BOUND,
    EVENT_EXTERNAL_INTR, // INTR pin via 8259A — EXT = 1
    EVENT_NMI
};

/* Error-code format for selector-related faults. [i386 Fig 9-7 p.161; SDM 3A Fig 7-7 p.3369] */
#define ERRCODE_EXT        (1u << 0)
#define ERRCODE_IDT        (1u << 1)
#define ERRCODE_TI         (1u << 2)
#define ERRCODE_INDEX_MASK 0xFFF8u
#define ERRCODE_SELECTOR(sel, ext)   (((sel) & 0xFFFCu) | ((ext) ? ERRCODE_EXT : 0u))
#define ERRCODE_IDT_VECTOR(vec, ext) (((u32)(vec) << 3) | ERRCODE_IDT | ((ext) ? ERRCODE_EXT : 0u))

/* Gate types accepted in the IDT. [i386 Fig 9-3 p.157] */
#define IDT_GATE_IS_TASK(t)  ((t) == DESC_SYS_TASKGATE)
#define IDT_GATE_IS_INT(t)   ((t) == DESC_SYS_INTGATE16 || (t) == DESC_SYS_INTGATE32)
#define IDT_GATE_IS_TRAP(t)  ((t) == DESC_SYS_TRAPGATE16 || (t) == DESC_SYS_TRAPGATE32)
#define IDT_GATE_IS_32BIT(t) ((t) == DESC_SYS_INTGATE32 || (t) == DESC_SYS_TRAPGATE32)

struct pending_exception {
    bool pending;
    u8   vector;
    bool has_error_code;
    u32  error_code;
    enum event_source source;
    u32  cr2;         // for #PF
};

/* Real-mode IVT entry. [i386 §14.3 p.209] */
struct ivt_entry {
    u16 offset;
    u16 segment;
};

struct cpu;

/* Raise an exception from inside an instruction: records it and longjmps to the step loop. */
O386_NORETURN void cpu_raise_exception(struct cpu *cpu, enum x86_exception vector, u32 error_code);
O386_NORETURN void cpu_raise_exception_noerr(struct cpu *cpu, enum x86_exception vector);
O386_NORETURN void cpu_raise_page_fault(struct cpu *cpu, u32 linear, u32 error_code);
O386_NORETURN void cpu_raise_gp0(struct cpu *cpu);

/* Deliver an event (called at an instruction boundary by the step loop). */
void cpu_deliver_event(struct cpu *cpu, u8 vector, enum event_source source, bool has_error_code, u32 error_code);
void cpu_deliver_real_mode(struct cpu *cpu, u8 vector);
void cpu_deliver_protected_mode(struct cpu *cpu, u8 vector, enum event_source source, bool has_error_code,
                                u32 error_code);
/* Push the interrupt frame for a procedure gate (with optional stack switch / V86 extension). [i386 Fig 9-5, Fig 15-3] */
void cpu_push_interrupt_frame(struct cpu *cpu, bool to_32bit_gate, bool privilege_change, bool from_v86,
                              u16 old_ss, u32 old_esp, bool has_error_code, u32 error_code);
/* IRET in all its forms: real mode, same level, inter-level, return to V86, task return (NT=1). [i386 IRET p.311] */
void cpu_iret(struct cpu *cpu, u8 opsize);

/* Double-fault / shutdown decision for a second exception raised while delivering the first.
 * [i386 §9.8.8 p.164; SDM 3A Table 7-5 p.3385] */
bool exception_is_contributory(enum x86_exception vector);
bool exception_causes_double_fault(enum x86_exception first, enum x86_exception second);
enum exception_class exception_class_of(enum x86_exception vector);
bool exception_has_error_code(enum x86_exception vector); /* [i386 Table 9-7 p.173] */
const char *exception_name(u8 vector);

/* Event-priority arbitration at an instruction boundary. [i386 §9.3 Table 9-2; SDM 3A §7.9 Table 7-2] */
bool cpu_service_pending_events(struct cpu *cpu);

#endif /* open386_CPU_INTERRUPT_H */
