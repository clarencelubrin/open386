/********************************************* Instruction Decoder *********************************************
 * @file decode.h
 * @author Lubrin, Clarence, U.
 * @details Instruction decoder types.
 *
 * @cite [i386 §17.2 p.240-246, Fig 17-1 instruction format, Fig 17-2 ModR/M & SIB,
 *       Tables 17-2 (16-bit ModR/M), 17-3 (32-bit ModR/M), 17-4 (SIB)];
 *      [i386 §17.1 p.239] operand-size / address-size attributes and 66h/67h prefixes;
 *      [SDM 2A §2.1 p.617-622, Tables 2-1/2-2/2-3]; [i386 §14.7 item 6 p.211] 15-byte limit → #GP.
 */
#ifndef open386_CPU_DECODE_H
#define open386_CPU_DECODE_H

#include "types.h"
#include "cpu/regs.h"

#define X86_MAX_INSN_LEN 15

/* Prefix bytes. [i386 §17.2 p.241] */
#define PREFIX_LOCK      0xF0
#define PREFIX_REPNE     0xF2
#define PREFIX_REP       0xF3 /* REP / REPE / REPZ */
#define PREFIX_SEG_CS    0x2E
#define PREFIX_SEG_SS    0x36
#define PREFIX_SEG_DS    0x3E
#define PREFIX_SEG_ES    0x26
#define PREFIX_SEG_FS    0x64
#define PREFIX_SEG_GS    0x65
#define PREFIX_OPSIZE    0x66
#define PREFIX_ADDRSIZE  0x67
#define OPCODE_ESCAPE_0F 0x0F

enum prefix_flags {
    PFX_LOCK     = 1u << 0,
    PFX_REPZ     = 1u << 1,
    PFX_REPNZ    = 1u << 2,
    PFX_OPSIZE   = 1u << 3,
    PFX_ADDRSIZE = 1u << 4,
    PFX_SEG      = 1u << 5
};

enum operand_kind {
    OPK_NONE = 0,
    OPK_REG,      // 16/32-bit general register (reg = enum x86_gpr)
    OPK_REG8,     // 8-bit general register (reg = enum x86_reg8)
    OPK_SREG,     // segment register
    OPK_CREG,
    OPK_DREG,
    OPK_TREG,
    OPK_MEM,      // memory operand: seg:ea
    OPK_IMM,      // immediate
    OPK_REL,      // relative branch target (already sign-extended)
    OPK_FAR_PTR,  // ptr16:16 / ptr16:32 immediate (far_sel:imm)
    OPK_MOFFS     // moffs8/16/32: direct offset without ModR/M (MOV A0-A3)
};

typedef struct operand {
    enum operand_kind kind;
    u8  size;     // bytes
    u8  reg;
    u8  seg;      // segment used for OPK_MEM / OPK_MOFFS
    u32 ea;       // effective address (offset within seg)
    u32 imm;
    u16 far_sel;
} Operand;

typedef struct modrm_byte {
    bool present;
    u8 raw;
    u8 mod;  // bits 7:6
    u8 reg;  // bits 5:3 — register or opcode extension
    u8 rm;   // bits 2:0
} ModRMByte;

typedef struct sib_byte {
    bool present;
    u8 raw;
    u8 scale; // bits 7:6 (ss)
    u8 index; // bits 5:3
    u8 base;  // bits 2:0
} SIBByte;

typedef struct opcode_entry OpcodeEntry; /* cpu/exec.h */

typedef struct x86_insn {
    u32 start_eip;          // EIP of the first byte; faults restore this
    u32 start_esp;          // ESP of the first byte
    u8  len;
    u8  bytes[X86_MAX_INSN_LEN];

    u8  prefixes;           // enum prefix_flags
    u8  prefix_count;
    u8  seg_override;       // enum x86_sreg or SEG_NONE
    u8  rep;                // 0, PREFIX_REP or PREFIX_REPNE

    bool two_byte;          // 0F xx
    u8  opcode;             // primary opcode byte (second byte when two_byte)
    ModRMByte modrm;
    SIBByte   sib;
    s32 disp;
    u8  disp_size;
    u32 imm;
    u8  imm_size;
    u32 imm2;               // second immediate: ENTER level, far pointer selector
    u8  imm2_size;

    u8  opsize;             // effective operand size: 2 or 4
    u8  addrsize;           // effective address size: 2 or 4

    const OpcodeEntry *entry;
    Operand ops[3];
    u8  op_count;
} X86Insn;

typedef struct cpu CPU;

/* Fetch and decode one instruction at CS:EIP. Raises #GP(0) past 15 bytes, #UD for invalid encodings
 * (including LOCK on a non-lockable form, [i386 LOCK p.336]). */
void decode_instruction(CPU *cpu, X86Insn *insn);
/* Compute the effective address for the ModR/M/SIB form in `insn`. [i386 §2.5.3.2 p.40, Fig 2-10] */
u32 decode_effective_address(CPU *cpu, const X86Insn *insn);
/* Default segment for a memory operand: SS for BP/EBP/ESP-based forms, else DS. [i386 §2.5.3.1 p.39] */
u8 decode_default_segment(const X86Insn *insn);
/* Resolve operand descriptors (App. A codes) into Operand entries. */
void decode_operands(CPU *cpu, X86Insn *insn);
/* Decode without touching CPU state (debugger/disassembler path). Returns length or -1. */
int decode_from_bytes(const u8 *bytes, size_t len, u32 eip, bool opsize32, bool addrsize32, X86Insn *insn);

#endif /* open386_CPU_DECODE_H */
