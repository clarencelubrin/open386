/********************************************** Control Transfer ********************************************
 * @file ops_ctrl.c
 * @author Lubrin, Clarence, U.
 * @details Implements control-transfer operation extension points.
 * 
 * Near form
 * - JMP, CALL, and RET transfer within the current code segment
 * - Subjected only to limit checking, no restricted control transfer check
 * 
 * Far form
 * - JMP and CALL refer to other segments. There are two ways JMP or CALL can refer to another segment:
 *      (a) The operand selects the descriptor of another executable segment
 *      (b) The operand selects the call gate descriptor.
 * - Require privilege checking. Two different privilege levels enter into a privilege check for a control transfer that does not use a call gate:
 *      -> CPL and DPL of the descriptor of the target segment
 * - The processor permits a JMP or CALL directly to another segment only if one of the following is satisfied:
 *      (1) DPL of the target is equal to CPL, or
 *      (2) The conforming bit of the target code-segment descriptor is set,
 *          and the DPL of the target is less than or equal to CPL
 * 
 * Conforming Segment
 * - Executable segment whose descriptor has the conforming bit set.
 * - The conforming-bit mechanism permits sharing procedures that may be called from various privilege levels but
 *   should execute at the privilege level of the calling procedure.
 * - When control is transferred to a conforming segment, CPL does not change.
 * 
 * Non-conforming Segment
 * - Control can be transferred without a gate only to executable segments at the same level of privilege
 * 
 * Call Gate
 * - Call gate descriptor reside in the GDT or LDT
 * - Has two primary functions:
 *      (1) To define an entry point of a procedure
 *      (2) To specify the privilege level of the entry point
 * - If destination selector refers to a gate selector -> operation of instruction is expanded as determined by the contents of the call gate
 * - Four different privilege levels are sed to check the validity of a control transfer via gate call:
 *      (1) CPL (current privilege level)   (2) RPL (requestor privilege level) of te selector used to specify the call gate
 *      (3) DPL of the gate selector        (4) DPL of the descriptor of the target executable segment
 * 
 * - Selector and offset field of gate form a pointer to the entry point of a procedure
 * - In far pointer operand, selector part of the pointer selects a gate, offset is not used
 * 
 * - Only CALL instructions can use gates to transfer to smaller privilege levels
 * - JMP instructions only transfer to an executable segment with same privilege level, or to a conforming segment
 * 
 * For JMP instruction to a nonconforming segment (Call Gate)
 *      (1) MAX (CPL, RPL) <= gate DPL
 *      (2) target segment DPL = CPL
 * For CALL instruction or JMP instruction to conforming segment
 *      (1) MAX (CPL, RPL) <= gate DPL
 *      (2) target segment DPL <= CPL
 * 
 * Format of Call Gate
 * 31               23              15               7               0
 * [            OFFSET              |P|DPL |  TYPE   |000|   DWORD   ]
 * [                                | |    |0|1|1|0|0|   |   COUNT   ]
 *              31...16
 * [           SELECTOR             |             OFFSET             ]
 *               15..0                           15..0
 */
#include "cpu/cpu.h"
#include "cpu/exec.h"

void op_jmp_rel(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_jmp_rm(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_jmp_far(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_jcc(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_call_rel(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_call_rm(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_call_far(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_ret_near(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_ret_far(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_loop(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_int_n(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_int3(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_into(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_iret(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void op_bound(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M1);
}
