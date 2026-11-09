/* open386 — disassembler (stub, M0). Shares tables with cpu/decode.c. */
#include "debugger/disasm.h"

int  disasm_one(const u8 *code, size_t len, const struct disasm_options *opts, char *out, size_t out_len) { O386_STUB_TODO(M1); return -1; }
int  disasm_insn(const struct x86_insn *insn, const struct disasm_options *opts, char *out, size_t out_len) { O386_STUB_TODO(M1); return -1; }
const char *disasm_operand_spec_name(u8 spec) { O386_STUB_TODO(M1); return ""; }
void disasm_format_operand(const struct x86_insn *insn, const struct operand *op, const struct disasm_options *opts,
                           char *out, size_t out_len) { O386_STUB_TODO(M1); }
