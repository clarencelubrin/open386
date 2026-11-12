/* open386 — IA-32 extension handlers, each gated by a CPU feature (PLAN.md §4.2; SDM Vol.2). */
#include "cpu/cpu.h"
#include "cpu/exec.h"

void op_cpuid(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_invlpg(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_wbinvd(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_invd(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_bswap(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_cmpxchg(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_xadd(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_rdtsc(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_rdmsr(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_wrmsr(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_cmpxchg8b(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_cmovcc(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
