/* open386 — control transfer handlers [i386 §3.5 p.65-69; §3.10.2 p.82; JMP p.319; CALL p.275; RET p.378; INT p.306; IRET p.311]. */
#include "cpu/cpu.h"
#include "cpu/exec.h"

void op_jmp_rel(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_jmp_rm(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_jmp_far(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_jcc(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_call_rel(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_call_rm(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_call_far(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_ret_near(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_ret_far(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_loop(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_int_n(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_int3(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_into(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_iret(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void op_bound(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
