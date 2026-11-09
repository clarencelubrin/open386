/* open386 — flag control handlers [i386 §3.8 p.79; PUSHF p.371; POPF p.366; STI p.400; CLI p.284]. */
#include "cpu/cpu.h"
#include "cpu/exec.h"

void op_clc(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_stc(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_cmc(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_cld(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_std(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_cli(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_sti(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_lahf(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_sahf(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_pushf(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_popf(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
