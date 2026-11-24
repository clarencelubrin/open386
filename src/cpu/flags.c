/********************************************* EFLAGS *********************************************
 * @file flags.c
 * @author Lubrin, Clarence, U.
 * @details EFLAGS and lazy status flags. cpu->eflags is only trustworthy for status flags when lazy.op == FLAGOP_NONE. Everything that reads/writes EFLAGS as a whole goes through wrapper functions.
 *          Ref: [i386 §2.3.4 p.33-35]; [i386 App. B p.417; App. C p.419; App. D p.421]; [i386 POPF p.366; IRET p.311].
 */
#include "cpu/cpu.h"

const char *const x86_cond_names[16] = {"O", "NO", "B", "NB", "E", "NE", "BE", "NBE",
                                        "S", "NS", "P", "NP", "L", "NL", "LE", "NLE"};

u32 cpu_get_eflags(CPU *cpu) {
    flags_materialize(cpu);
    return cpu->eflags | EFLAGS_RSVD1;
}
void cpu_set_eflags(CPU *cpu, u32 value, u32 mask) {
    O386_STUB_TODO(M1);
    // Materialize
    // Apply the mask
    // Force bit 1 on
    // Clear lazy.op
}
void flags_set_lazy(CPU *cpu, enum flag_op op, u8 size, u32 src1, u32 src2, u32 result, u32 aux) {
    O386_STUB_TODO(M1);
}
void flags_materialize(CPU *cpu) {
    if(cpu->lazy.op == FLAGOP_NONE) return;
    // Compute CF, PF, AF, ZF, SF, OF from lazy {op, size, src1, src2, result, aux}

    // FLAGOP_INC
    // opcode INC/DEC preserve CF. When they set up lazy state, they must first materialize the previous op
    // so the old CF is in EFLAGS

    // UNIMPLEMENTED: log then abort
    LOG(LOG_ERROR, LOGC_CPU, "flag_materialize opcode instruction not supported");
    abort();

    u32 computed_bits = 0;
    cpu->eflags = (cpu->eflags & ~EFLAGS_STATUS_MASK) | computed_bits;
    cpu->lazy.op = FLAGOP_NONE;
}
bool flags_get(CPU *cpu, u32 flag_bit) {
    if(flag_bit & EFLAGS_STATUS_MASK) flags_materialize(cpu);
    return (cpu->eflags & flag_bit) != 0;
}
void flags_set(CPU *cpu, u32 flag_bit, bool value) {
    if(flag_bit & EFLAGS_STATUS_MASK) flags_materialize(cpu);
    // Set or clear bit in EFLAG
    if(value) cpu->eflags |= flag_bit;
    else      cpu->eflags &= (~flag_bit);
}
bool cpu_test_condition(CPU *cpu, enum x86_cond cond) {
    O386_STUB_TODO(M1);
    return false;
}
bool flags_parity_even(u8 value) {
    O386_STUB_TODO(M1);
    return false;
}
u32 flags_popf_writable_mask(const CPU *cpu, u8 opsize) {
    O386_STUB_TODO(M2);
    return 0;
}
