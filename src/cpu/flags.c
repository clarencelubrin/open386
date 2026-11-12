/*
 * open386 — EFLAGS and lazy status flags.
 * Ref: [i386 §2.3.4 p.33-35]; [i386 App. B p.417; App. C p.419; App. D p.421]; [i386 POPF p.366; IRET p.311].
 */
#include "cpu/cpu.h"

const char *const x86_cond_names[16] = {"O", "NO", "B", "NB", "E", "NE", "BE", "NBE",
                                        "S", "NS", "P", "NP", "L", "NL", "LE", "NLE"};

u32 cpu_get_eflags(CPU *cpu) {
    O386_STUB_TODO(M1);
    return 0;
}
void cpu_set_eflags(CPU *cpu, u32 value, u32 mask) {
    O386_STUB_TODO(M1);
}
void flags_set_lazy(CPU *cpu, enum flag_op op, u8 size, u32 src1, u32 src2, u32 result, u32 aux) {
    O386_STUB_TODO(M1);
}
void flags_materialize(CPU *cpu) {
    O386_STUB_TODO(M1);
}
bool flags_get(CPU *cpu, u32 flag_bit) {
    O386_STUB_TODO(M1);
    return false;
}
void flags_set(CPU *cpu, u32 flag_bit, bool value) {
    O386_STUB_TODO(M1);
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
