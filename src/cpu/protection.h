/*
 * open386 — privilege checks, far control transfers through gates, I/O protection.
 *
 * Ref: [i386 Ch.6 p.106-129: §6.3.1.3 privilege levels, §6.3.2 data access Fig 6-3, §6.3.3 control transfers
 *       Fig 6-4, §6.3.4 call gates Fig 6-5/6-6/6-7, §6.3.4.1 stack switching Fig 6-8/6-9, §6.3.4.2 return
 *       Table 6-3, §6.3.5 privileged/sensitive, §6.3.6 pointer validation]; [i386 §8.3 p.148-151 IOPL/IOPB];
 *      [i386 §15.4 p.224 V86 sensitive instructions]; [SDM 3A Ch.6 p.3317-3350, Fig 6-4..6-13; Vol.1 §20.5].
 */
#ifndef open386_CPU_PROTECTION_H
#define open386_CPU_PROTECTION_H

#include "types.h"
#include "cpu/segment.h"

struct cpu;

/* Data-segment access rule: max(CPL, RPL) <= DPL (conforming code: no check). [i386 Fig 6-3 p.114] */
bool prot_data_access_allowed(const struct cpu *cpu, const struct segment_descriptor *d, u8 rpl);
/* Privileged instruction at CPL != 0 → #GP(0). [i386 §6.3.5.1 p.123] */
void prot_require_cpl0(struct cpu *cpu);
/* IOPL check for CLI/STI/IN/OUT…: protected mode requires CPL <= IOPL; V86 uses the IOPB for I/O. */
bool prot_iopl_permits(const struct cpu *cpu);
void prot_check_io(struct cpu *cpu, u16 port, u8 size);            /* #GP(0) on violation [i386 §8.3] */
void prot_check_iopl_sensitive(struct cpu *cpu);                    /* CLI/STI/PUSHF/POPF/INT n/IRET in V86 */

/* Far transfers (protected mode). The callers are JMP/CALL far, RET far, and the gate paths. */
void prot_far_jump(struct cpu *cpu, u16 selector, u32 offset, u8 opsize);                /* [i386 JMP p.319] */
void prot_far_call(struct cpu *cpu, u16 selector, u32 offset, u8 opsize);                /* [i386 CALL p.275] */
void prot_far_return(struct cpu *cpu, u16 pop_bytes, u8 opsize);                          /* [i386 RET p.378] */
/* Transfer through a call gate: privilege check, parameter copy, stack switch. [i386 §6.3.4 p.116-121] */
void prot_call_gate_transfer(struct cpu *cpu, u16 gate_selector, const struct gate_descriptor *gate,
                             bool is_call, u8 opsize);
/* Direct transfer to a code segment (conforming or not) with the rules of [i386 §6.3.3 p.115]. */
void prot_code_segment_transfer(struct cpu *cpu, u16 selector, const struct segment_descriptor *d, u32 offset,
                                bool is_call, u8 opsize);
/* Copy `count` parameters from the outer stack during an inter-level call. [i386 §6.3.4.1 p.119] */
void prot_copy_gate_parameters(struct cpu *cpu, u16 old_ss, u32 old_esp, u8 count, bool dword_params);

/* Pointer-validation helpers (ARPL/LAR/LSL/VERR/VERW). Return false when the selector is not accessible
 * (ZF semantics), never fault. [i386 §6.3.6 p.124-126; SDM 3A §6.10 p.3340] */
bool prot_validate_descriptor(struct cpu *cpu, u16 selector, struct segment_descriptor *out, struct descriptor_raw *raw);
bool prot_lar_allowed(const struct cpu *cpu, const struct segment_descriptor *d, u8 rpl);
bool prot_lsl_allowed(const struct cpu *cpu, const struct segment_descriptor *d, u8 rpl);
bool prot_verr_allowed(const struct cpu *cpu, const struct segment_descriptor *d, u8 rpl);
bool prot_verw_allowed(const struct cpu *cpu, const struct segment_descriptor *d, u8 rpl);

#endif /* open386_CPU_PROTECTION_H */
