/********************************************* Executor *********************************************
 * @file exec.h
 * @author Lubrin, Clarence, U.
 * @details Opcode tables and instruction handler declarations.
 *
 * Handlers are grouped by the instruction classes of [i386 Ch.3 p.45-84] (one exec_*.c file each)
 * and each handler's doc comment cites its page in [i386 Ch.17 p.256-411]. Operand-form codes use the
 * manual's own abbreviations [i386 App. A p.412; SDM 2D §A.2 p.2989].
 */
#ifndef open386_CPU_EXEC_H
#define open386_CPU_EXEC_H

#include "types.h"
#include "cpu/decode.h"
#include "cpu/features.h"

typedef struct cpu CPU;

typedef void (*insn_handler)(CPU *cpu, X86Insn *insn);

enum opcode_flags {
    OPF_MODRM          = 1u << 0,  // a ModR/M byte follows
    OPF_GROUP          = 1u << 1,  // ModR/M.reg selects the entry in opcode_groups[]
    OPF_PRIVILEGED     = 1u << 2,  // CPL must be 0 [i386 §6.3.5.1 p.123]
    OPF_IOPL_SENSITIVE = 1u << 3,  // IN/OUT/INS/OUTS/CLI/STI [i386 §6.3.5.2 p.124; §8.3 p.148]
    OPF_LOCKABLE       = 1u << 4,  // LOCK prefix legal with a memory destination [i386 LOCK p.336]
    OPF_STRING         = 1u << 5,  // REP prefixes apply [i386 §3.6.1 p.70]
    OPF_FPU_ESC        = 1u << 6,  // D8-DF escape: route to fpu_exec_esc() [i386 §11.1.2 p.189]
    OPF_INVALID        = 1u << 7,  // #UD [i386 §9.8.6 p.164]
    OPF_MEM_ONLY       = 1u << 8,  // ModR/M must address memory (M, Mp, Ma forms) else #UD
    OPF_REAL_UD        = 1u << 9,  // #UD in real mode: VERR VERW LAR LSL LTR STR LLDT SLDT [i386 §14.2 p.208]
    OPF_V86_SENSITIVE  = 1u << 10, // sensitive in V86 mode [i386 §15.4 p.224]
    OPF_ALIAS          = 1u << 11, // reserved encoding that aliases another instruction [SDM 3B §25.15 p.4128]
    OPF_PREFIX         = 1u << 12  // byte is a prefix, consumed by the decoder
};

/* Operand specifiers: addressing-method letter + operand-type letter. [i386 App. A p.412-413] */
enum operand_spec {
    OPS_NONE = 0,
    OPS_Eb, OPS_Ev, OPS_Ew, OPS_Ed,         // ModR/M r/m: reg or mem
    OPS_Gb, OPS_Gv, OPS_Gw,                 // ModR/M reg field
    OPS_Ib, OPS_Iv, OPS_Iw, OPS_Ibs,        // immediates (Ibs = sign-extended byte)
    OPS_Jb, OPS_Jv,                         // relative offsets
    OPS_Ap,                                 // far pointer immediate
    OPS_Ob, OPS_Ov,                         // moffs
    OPS_M,  OPS_Ma, OPS_Mp, OPS_Ms, OPS_Mq, // memory-only forms (LEA, BOUND, LxS, LGDT/LIDT, x87)
    OPS_Sw,                                 // segment register in reg field
    OPS_Cd, OPS_Dd, OPS_Td,                 // control/debug/test register in reg field
    OPS_Rd,                                 // general register in r/m (mod must be 11)
    OPS_Xb, OPS_Xv,                         // DS:[E]SI string source
    OPS_Yb, OPS_Yv,                         // ES:[E]DI string destination
    OPS_Zb, OPS_Zv,                         // register encoded in opcode bits 2:0
    OPS_AL, OPS_eAX, OPS_DX, OPS_CL, OPS_1, // fixed operands
    OPS_ES, OPS_CS, OPS_SS, OPS_DS, OPS_FS, OPS_GS,
    OPS_COUNT
};

enum opcode_group {
    GRP1_80 = 0, GRP1_81, GRP1_82, GRP1_83,              // ADD OR ADC SBB AND SUB XOR CMP
    GRP2_C0, GRP2_C1, GRP2_D0, GRP2_D1, GRP2_D2, GRP2_D3, // ROL ROR RCL RCR SHL SHR (SAL alias) SAR
    GRP3_F6, GRP3_F7,                                     // TEST (/1 alias) NOT NEG MUL IMUL DIV IDIV
    GRP4_FE,                                              // INC DEC
    GRP5_FF,                                              // INC DEC CALL CALLF JMP JMPF PUSH
    GRP6_0F00,                                            // SLDT STR LLDT LTR VERR VERW
    GRP7_0F01,                                            // SGDT SIDT LGDT LIDT SMSW LMSW (INVLPG gated)
    GRP8_0FBA,                                            // BT BTS BTR BTC with imm8
    OPCODE_GROUP_COUNT
};

typedef struct opcode_entry {
    const char  *mnemonic;
    insn_handler handler;
    u16  flags;               // enum opcode_flags
    u8   operands[3];         // enum operand_spec
    u8   clocks;              // base clock count, "Clocks" column [i386 §17.2.2.3 p.248]; 0 = n/a
    u8   required_feature;    // enum cpu_feature, CPUF_NONE if part of the 386 base
    u8   group;               // enum opcode_group when OPF_GROUP
} OpcodeEntry;

/* Populated by exec_tables_init() from the transcription of [i386 App. A] (see tools/README.md). */
extern OpcodeEntry opcode_table_1byte[256];
extern OpcodeEntry opcode_table_2byte[256];
extern OpcodeEntry opcode_groups[OPCODE_GROUP_COUNT][8];

void exec_tables_init(void);
void exec_instruction(CPU *cpu, X86Insn *insn);
/* Common checks performed before a handler runs: feature gate, privilege, IOPL, LOCK legality, mode. */
void exec_precheck(CPU *cpu, const X86Insn *insn);

/* Operand access helpers shared by all handlers. */
u32 exec_read_operand(CPU *cpu, const X86Insn *insn, const Operand *op);
void exec_write_operand(CPU *cpu, const X86Insn *insn, const Operand *op, u32 value);
u32 exec_sign_extend(u32 value, u8 from_size, u8 to_size);
u32 exec_size_mask(u8 size);

/* ---- exec_data.c — data movement [i386 §3.1 p.45-50] ---- */
void op_mov(CPU *, X86Insn *);        /* [i386 MOV p.345] */
void op_mov_sreg(CPU *, X86Insn *);   /* MOV Sreg,r/m16 / MOV r/m16,Sreg [i386 MOV p.345] */
void op_mov_moffs(CPU *, X86Insn *);  /* A0-A3 */
void op_xchg(CPU *, X86Insn *);       /* [i386 XCHG p.409] */
void op_push(CPU *, X86Insn *);       /* [i386 PUSH p.367] */
void op_push_imm(CPU *, X86Insn *);
void op_push_sreg(CPU *, X86Insn *);
void op_pop(CPU *, X86Insn *);        /* [i386 POP p.361] */
void op_pop_sreg(CPU *, X86Insn *);
void op_pusha(CPU *, X86Insn *);      /* [i386 PUSHA p.369] */
void op_popa(CPU *, X86Insn *);       /* [i386 POPA p.364] */
void op_movsx(CPU *, X86Insn *);      /* [i386 MOVSX p.350] */
void op_movzx(CPU *, X86Insn *);      /* [i386 MOVZX p.351] */
void op_cbw_cwde(CPU *, X86Insn *);   /* [i386 CBW/CWDE p.281] */
void op_cwd_cdq(CPU *, X86Insn *);    /* [i386 CWD/CDQ p.290] */
void op_lea(CPU *, X86Insn *);        /* [i386 LEA p.327] */
void op_xlat(CPU *, X86Insn *);       /* [i386 XLAT p.410] */

/* ---- exec_arith.c — binary arithmetic [i386 §3.2 p.50-53] ---- */
void op_add(CPU *, X86Insn *);        /* [i386 ADD p.261] */
void op_adc(CPU *, X86Insn *);        /* [i386 ADC p.260] */
void op_sub(CPU *, X86Insn *);        /* [i386 SUB p.404] */
void op_sbb(CPU *, X86Insn *);        /* [i386 SBB p.386] */
void op_cmp(CPU *, X86Insn *);        /* [i386 CMP p.287] */
void op_inc(CPU *, X86Insn *);        /* [i386 INC p.303] */
void op_dec(CPU *, X86Insn *);        /* [i386 DEC p.293] */
void op_neg(CPU *, X86Insn *);        /* [i386 NEG p.354] */
void op_mul(CPU *, X86Insn *);        /* [i386 MUL p.352] */
void op_imul(CPU *, X86Insn *);       /* one-, two- and three-operand forms [i386 IMUL p.300] */
void op_div(CPU *, X86Insn *);        /* [i386 DIV p.294]; #DE on /0 or overflow */
void op_idiv(CPU *, X86Insn *);       /* [i386 IDIV p.298]; 80h/8000h quotient OK on 386 [SDM 3B §25.25] */

/* ---- exec_decimal.c — BCD [i386 §3.3 p.53-54] ---- */
void op_daa(CPU *, X86Insn *);        /* [i386 DAA p.291] */
void op_das(CPU *, X86Insn *);        /* [i386 DAS p.292] */
void op_aaa(CPU *, X86Insn *);        /* [i386 AAA p.256] */
void op_aas(CPU *, X86Insn *);        /* [i386 AAS p.259] */
void op_aam(CPU *, X86Insn *);        /* [i386 AAM p.258]; imm8 base, #DE when 0 */
void op_aad(CPU *, X86Insn *);        /* [i386 AAD p.257] */

/* ---- exec_logic.c — logical, bit, shift, rotate, SETcc, TEST [i386 §3.4 p.54-65] ---- */
void op_and(CPU *, X86Insn *);        /* [i386 AND p.262] */
void op_or(CPU *, X86Insn *);         /* [i386 OR p.357] */
void op_xor(CPU *, X86Insn *);        /* [i386 XOR p.411] */
void op_not(CPU *, X86Insn *);        /* [i386 NOT p.356] */
void op_test(CPU *, X86Insn *);       /* [i386 TEST p.405] */
void op_bt(CPU *, X86Insn *);         /* [i386 BT p.267; Fig 17-3/17-4 bit addressing] */
void op_bts(CPU *, X86Insn *);        /* [i386 BTS p.273] */
void op_btr(CPU *, X86Insn *);        /* [i386 BTR p.271] */
void op_btc(CPU *, X86Insn *);        /* [i386 BTC p.269] */
void op_bsf(CPU *, X86Insn *);        /* [i386 BSF p.265] */
void op_bsr(CPU *, X86Insn *);        /* [i386 BSR p.266] */
void op_shl(CPU *, X86Insn *);        /* SAL/SHL [i386 p.383]; count masked to 5 bits */
void op_shr(CPU *, X86Insn *);
void op_sar(CPU *, X86Insn *);
void op_rol(CPU *, X86Insn *);        /* [i386 RCL/RCR/ROL/ROR p.372] */
void op_ror(CPU *, X86Insn *);
void op_rcl(CPU *, X86Insn *);
void op_rcr(CPU *, X86Insn *);
void op_shld(CPU *, X86Insn *);       /* [i386 SHLD p.392] */
void op_shrd(CPU *, X86Insn *);       /* [i386 SHRD p.394] */
void op_setcc(CPU *, X86Insn *);      /* [i386 SETcc p.389] */

/* ---- exec_control.c — control transfer [i386 §3.5 p.65-69; §3.10.2 p.82] ---- */
void op_jmp_rel(CPU *, X86Insn *);    /* [i386 JMP p.319] */
void op_jmp_rm(CPU *, X86Insn *);     /* JMP r/m (near indirect) */
void op_jmp_far(CPU *, X86Insn *);    /* ptr16:32 / m16:32; may enter a gate or task */
void op_jcc(CPU *, X86Insn *);        /* [i386 Jcc p.316] incl. JCXZ/JECXZ */
void op_call_rel(CPU *, X86Insn *);   /* [i386 CALL p.275] */
void op_call_rm(CPU *, X86Insn *);
void op_call_far(CPU *, X86Insn *);
void op_ret_near(CPU *, X86Insn *);   /* [i386 RET p.378] */
void op_ret_far(CPU *, X86Insn *);
void op_loop(CPU *, X86Insn *);       /* LOOP/LOOPE/LOOPNE [i386 p.340] */
void op_int_n(CPU *, X86Insn *);      /* [i386 INT p.306] */
void op_int3(CPU *, X86Insn *);       /* one-byte CCh */
void op_into(CPU *, X86Insn *);
void op_iret(CPU *, X86Insn *);       /* [i386 IRET p.311] */
void op_bound(CPU *, X86Insn *);      /* [i386 BOUND p.264] → #BR */

/* ---- exec_string.c — string operations [i386 §3.6 p.69-72] ---- */
void op_movs(CPU *, X86Insn *);       /* [i386 MOVS p.348] */
void op_cmps(CPU *, X86Insn *);       /* [i386 CMPS p.288] */
void op_scas(CPU *, X86Insn *);       /* [i386 SCAS p.387] */
void op_lods(CPU *, X86Insn *);       /* [i386 LODS p.338] */
void op_stos(CPU *, X86Insn *);       /* [i386 STOS p.401] */
void op_ins(CPU *, X86Insn *);        /* [i386 INS p.304] */
void op_outs(CPU *, X86Insn *);       /* [i386 OUTS p.359] */

/* ---- exec_hll.c — block-structured language support [i386 §3.7 p.72-78] ---- */
void op_enter(CPU *, X86Insn *);      /* [i386 ENTER p.295] */
void op_leave(CPU *, X86Insn *);      /* [i386 LEAVE p.329] */

/* ---- exec_flags.c — flag control [i386 §3.8 p.79] ---- */
void op_clc(CPU *, X86Insn *);
void op_stc(CPU *, X86Insn *);
void op_cmc(CPU *, X86Insn *);
void op_cld(CPU *, X86Insn *);
void op_std(CPU *, X86Insn *);
void op_cli(CPU *, X86Insn *);        /* [i386 CLI p.284] IOPL-sensitive */
void op_sti(CPU *, X86Insn *);        /* [i386 STI p.400] one-instruction shadow */
void op_lahf(CPU *, X86Insn *);       /* [i386 LAHF p.324] */
void op_sahf(CPU *, X86Insn *);       /* [i386 SAHF p.382] */
void op_pushf(CPU *, X86Insn *);      /* [i386 PUSHF p.371] */
void op_popf(CPU *, X86Insn *);       /* [i386 POPF p.366] */

/* ---- exec_segment.c — segment register instructions [i386 §3.10 p.81-83] ---- */
void op_lxs(CPU *, X86Insn *);        /* LDS/LES/LFS/LGS/LSS [i386 p.332] */

/* ---- exec_system.c — system instructions [i386 §4.2 p.89; Ch.6; Ch.7; Ch.10] ---- */
void op_lgdt(CPU *, X86Insn *);       /* [i386 LGDT/LIDT p.330] */
void op_lidt(CPU *, X86Insn *);
void op_sgdt(CPU *, X86Insn *);       /* [i386 SGDT/SIDT p.391] */
void op_sidt(CPU *, X86Insn *);
void op_lldt(CPU *, X86Insn *);       /* [i386 LLDT p.334] */
void op_sldt(CPU *, X86Insn *);       /* [i386 SLDT p.396] */
void op_ltr(CPU *, X86Insn *);        /* [i386 LTR p.344] */
void op_str(CPU *, X86Insn *);        /* [i386 STR p.403] */
void op_lmsw(CPU *, X86Insn *);       /* [i386 LMSW p.335] */
void op_smsw(CPU *, X86Insn *);       /* [i386 SMSW p.397] */
void op_clts(CPU *, X86Insn *);       /* [i386 CLTS p.285] */
void op_mov_cr(CPU *, X86Insn *);     /* [i386 MOV special p.347] */
void op_mov_dr(CPU *, X86Insn *);
void op_mov_tr(CPU *, X86Insn *);     /* gated CPUF_TEST_REGS */
void op_lar(CPU *, X86Insn *);        /* [i386 LAR p.325] */
void op_lsl(CPU *, X86Insn *);        /* [i386 LSL p.342] */
void op_verr(CPU *, X86Insn *);       /* [i386 VERR/VERW p.406] */
void op_verw(CPU *, X86Insn *);
void op_arpl(CPU *, X86Insn *);       /* [i386 ARPL p.263] */
void op_hlt(CPU *, X86Insn *);        /* [i386 HLT p.297] */
void op_in(CPU *, X86Insn *);         /* [i386 IN p.302] */
void op_out(CPU *, X86Insn *);        /* [i386 OUT p.358] */

/* ---- exec_misc.c ---- */
void op_nop(CPU *, X86Insn *);        /* [i386 NOP p.355] */
void op_wait(CPU *, X86Insn *);       /* [i386 WAIT p.408] */
void op_undefined(CPU *, X86Insn *);  /* #UD [i386 §9.8.6 p.164] */

/* ---- exec_fpu.c — ESC dispatch [i386 §3.9 p.80; §11.1 p.189] ---- */
void op_esc(CPU *, X86Insn *);

/* ---- IA-32 extensions (gated; PLAN.md §4.2) ---- */
void op_cpuid(CPU *, X86Insn *);      /* CPUF_CPUID     [SDM 2A CPUID] */
void op_invlpg(CPU *, X86Insn *);     /* CPUF_486_INSNS [SDM 2A INVLPG] */
void op_wbinvd(CPU *, X86Insn *);     /* CPUF_486_INSNS [SDM 2C WBINVD] */
void op_invd(CPU *, X86Insn *);       /* CPUF_486_INSNS [SDM 2A INVD] */
void op_bswap(CPU *, X86Insn *);      /* CPUF_486_INSNS [SDM 2A BSWAP] */
void op_cmpxchg(CPU *, X86Insn *);    /* CPUF_486_INSNS [SDM 2A CMPXCHG] */
void op_xadd(CPU *, X86Insn *);       /* CPUF_486_INSNS [SDM 2C XADD] */
void op_rdtsc(CPU *, X86Insn *);      /* CPUF_TSC       [SDM 2B RDTSC] */
void op_rdmsr(CPU *, X86Insn *);      /* CPUF_MSR       [SDM 2B RDMSR] */
void op_wrmsr(CPU *, X86Insn *);      /* CPUF_MSR       [SDM 2C WRMSR] */
void op_cmpxchg8b(CPU *, X86Insn *);  /* CPUF_CX8       [SDM 2A CMPXCHG8B] */
void op_cmovcc(CPU *, X86Insn *);     /* CPUF_CMOV      [SDM 2A CMOVcc] */

#endif /* open386_CPU_EXEC_H */
