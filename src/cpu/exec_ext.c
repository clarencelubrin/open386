/* open386 — IA-32 extension handlers, each gated by a CPU feature (PLAN.md §4.2; SDM Vol.2). */
#include "cpu/cpu.h"
#include "cpu/exec.h"

void op_cpuid(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
void op_invlpg(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
void op_wbinvd(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
void op_invd(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
void op_bswap(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
void op_cmpxchg(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
void op_xadd(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
void op_rdtsc(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
void op_rdmsr(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
void op_wrmsr(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
void op_cmpxchg8b(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
void op_cmovcc(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M1);
}
