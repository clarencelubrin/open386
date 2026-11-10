/* open386 — debug registers. Ref: [i386 Ch.12 p.195-203; SDM 3B §20.2-20.3]. */
#include "cpu/cpu.h"

void debug_reset(struct cpu *cpu) {
    O386_STUB_TODO(M2);
}
void debug_check_instruction_breakpoint(struct cpu *cpu, u32 linear_eip) {
    O386_STUB_TODO(M2);
}
void debug_check_data_breakpoint(struct cpu *cpu, u32 linear, u8 size, bool is_write) {
    O386_STUB_TODO(M2);
}
void debug_deliver_pending_traps(struct cpu *cpu) {
    O386_STUB_TODO(M2);
}
void debug_on_task_switch(struct cpu *cpu, bool new_task_t_bit) {
    O386_STUB_TODO(M3);
}
u32 debug_read_dr(struct cpu *cpu, u8 n) {
    O386_STUB_TODO(M2);
    return 0;
}
void debug_write_dr(struct cpu *cpu, u8 n, u32 value) {
    O386_STUB_TODO(M2);
}
bool debug_breakpoint_matches(const struct cpu *cpu, u8 n, u32 linear, u8 size, enum dr_rw access) {
    O386_STUB_TODO(M2);
    return false;
}
