/* open386 — NOP, WAIT and undefined-opcode handlers [i386 §3.11 p.83; NOP p.355; WAIT p.408; §9.8.6 p.164]. */
#include "cpu/cpu.h"
#include "cpu/exec.h"

void op_nop(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
void op_wait(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
void op_undefined(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
