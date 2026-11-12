/********************************************* Opcode Table *********************************************
 * @file opcode_table.c
 * @author Lubrin, Clarence, U.
 * @details Opcode tables.
 *          To be generated from a line-by-line transcription of [i386 App. A p.412-416] cross-checked against
 *          [SDM 2D Tables A-2, A-3, A-6 p.2994-3008] by tools/gen_opcode_table.py (see tools/README.md).
 *          Zero-initialised in M0: every entry decodes as invalid until the table is filled.
 */
#include "cpu/exec.h"

OpcodeEntry opcode_table_1byte[256];
OpcodeEntry opcode_table_2byte[256];
OpcodeEntry opcode_groups[OPCODE_GROUP_COUNT][8];

void exec_tables_init(void) {
    O386_STUB_TODO(M1);
}
