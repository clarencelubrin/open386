/*
 * open386 — disassembler sharing the decoder tables (so trace text is a second check on the decoder).
 * Output syntax: Intel, as in [i386 Ch.17] instruction pages.
 */
#ifndef open386_DEBUGGER_DISASM_H
#define open386_DEBUGGER_DISASM_H

#include "types.h"
#include "cpu/decode.h"

typedef struct disasm_options {
    bool opsize32;
    bool addrsize32;
    u32  eip;           // address of the first byte, for relative targets
    bool show_bytes;
    bool uppercase;
} DisasmOptions;

/* Disassemble one instruction. Returns its length in bytes, or -1 for an invalid/undecodable sequence. */
int disasm_one(const u8 *code, size_t len, const DisasmOptions *opts, char *out, size_t out_len);
int disasm_insn(const X86Insn *insn, const DisasmOptions *opts, char *out, size_t out_len);
const char *disasm_operand_spec_name(u8 spec);
void disasm_format_operand(const X86Insn *insn, const Operand *op, const DisasmOptions *opts,
                           char *out, size_t out_len);

#endif /* open386_DEBUGGER_DISASM_H */
