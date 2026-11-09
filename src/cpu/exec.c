/* open386 — executor entry and operand helpers. Ref: [i386 §17.2.2 p.246-255 how to read the instruction pages]. */
#include "cpu/cpu.h"
#include "cpu/exec.h"

void exec_instruction(struct cpu *cpu, struct x86_insn *insn) { O386_STUB_TODO(M1); }
void exec_precheck(struct cpu *cpu, const struct x86_insn *insn) { O386_STUB_TODO(M1); }
u32  exec_read_operand(struct cpu *cpu, const struct x86_insn *insn, const struct operand *op) { O386_STUB_TODO(M1); return 0; }
void exec_write_operand(struct cpu *cpu, const struct x86_insn *insn, const struct operand *op, u32 value) { O386_STUB_TODO(M1); }
u32  exec_sign_extend(u32 value, u8 from_size, u8 to_size) { O386_STUB_TODO(M1); return 0; }
u32  exec_size_mask(u8 size) { O386_STUB_TODO(M1); return 0; }
