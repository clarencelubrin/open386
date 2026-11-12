/********************************************* Instruction Decoder *********************************************
 * @file decode.c
 * @author Lubrin, Clarence, U.
 * @details Instruction decoder.
 *          Ref: [i386 §17.2 p.240-246, Tables 17-2/17-3/17-4]; [SDM 2A §2.1 Tables 2-1/2-2/2-3]; [i386 §14.7 item 6 p.211].
 */
#include "cpu/cpu.h"
#include "cpu/exec.h"

void decode_instruction(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
u32 decode_effective_address(CPU *cpu, const X86Insn *insn) {
    O386_STUB_TODO(M1);
    return 0;
}
u8 decode_default_segment(const X86Insn *insn) {
    O386_STUB_TODO(M1);
    return SEG_DS;
}
void decode_operands(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
int decode_from_bytes(const u8 *bytes, size_t len, u32 eip, bool opsize32, bool addrsize32, X86Insn *insn) {
    O386_STUB_TODO(M1);
    return -1;
}
