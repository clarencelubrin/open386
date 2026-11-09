/*
 * open386 — 80387 numeric coprocessor: CPU interface, state images and (later) arithmetic.
 *
 * Ref: [i386 Ch.11 §11.1 p.189-192: ESC/WAIT, EM/MP/TS, coprocessor exceptions]; [i386 §3.9 p.80];
 *      [SDM 1 Ch.8 p.209-242: §8.1.2 register stack Fig 8-2, §8.1.3 status word Fig 8-4, §8.1.5 control word
 *       Fig 8-6, §8.1.7 tag word Fig 8-7, §8.1.8-8.1.9 pointers/opcode Fig 8-8, §8.1.10 FSAVE/FSTENV images
 *       Fig 8-9..8-12, §8.2 data types Fig 8-13, §8.3 instruction set, §8.4-8.7 exceptions];
 *      [SDM 3A §2.5 Table 2-2 EM/MP/TS actions]; [SDM 3B §25.18 p.4129 387 vs later];
 *      [SDM 2D §A.5 p.3009 escape opcode maps]; reset/FINIT values [SDM 3A Table 12-1 p.3523].
 * ICS-OS: fninit at boot, fnsave/frstor per context switch (kernel/process/process.c:1283-1302, 1598-1600).
 */
#ifndef open386_CPU_FPU_H
#define open386_CPU_FPU_H

#include "types.h"

/* 80-bit double extended precision value. [SDM 1 §4.8.2 p.104; Fig 8-13] */
struct fp80 {
    u64 mantissa;   /* explicit integer bit 63 */
    u16 sign_exp;   /* bit 15 sign, bits 14:0 biased exponent (bias 16383) */
};

/* Control word. [SDM 1 Fig 8-6 p.215] */
#define FPU_CW_IM        (1u << 0)
#define FPU_CW_DM        (1u << 1)
#define FPU_CW_ZM        (1u << 2)
#define FPU_CW_OM        (1u << 3)
#define FPU_CW_UM        (1u << 4)
#define FPU_CW_PM        (1u << 5)
#define FPU_CW_PC_SHIFT  8
#define FPU_CW_PC_MASK   (3u << FPU_CW_PC_SHIFT)
#define FPU_CW_RC_SHIFT  10
#define FPU_CW_RC_MASK   (3u << FPU_CW_RC_SHIFT)
#define FPU_CW_IC        (1u << 12) /* infinity control: ignored by the 387 [SDM 1 §8.1.6 p.216] */
#define FPU_CW_FINIT     0x037Fu    /* [SDM 3A Table 12-1] */

enum fpu_precision { FPU_PC_SINGLE = 0, FPU_PC_RESERVED = 1, FPU_PC_DOUBLE = 2, FPU_PC_EXTENDED = 3 };
enum fpu_rounding  { FPU_RC_NEAREST = 0, FPU_RC_DOWN = 1, FPU_RC_UP = 2, FPU_RC_ZERO = 3 };

/* Status word. [SDM 1 Fig 8-4 p.212] */
#define FPU_SW_IE        (1u << 0)
#define FPU_SW_DE        (1u << 1)
#define FPU_SW_ZE        (1u << 2)
#define FPU_SW_OE        (1u << 3)
#define FPU_SW_UE        (1u << 4)
#define FPU_SW_PE        (1u << 5)
#define FPU_SW_SF        (1u << 6)
#define FPU_SW_ES        (1u << 7)
#define FPU_SW_C0        (1u << 8)
#define FPU_SW_C1        (1u << 9)
#define FPU_SW_C2        (1u << 10)
#define FPU_SW_TOP_SHIFT 11
#define FPU_SW_TOP_MASK  (7u << FPU_SW_TOP_SHIFT)
#define FPU_SW_C3        (1u << 14)
#define FPU_SW_B         (1u << 15)

/* Tag word values, two bits per register. [SDM 1 §8.1.7 p.216] */
enum fpu_tag { FPU_TAG_VALID = 0, FPU_TAG_ZERO = 1, FPU_TAG_SPECIAL = 2, FPU_TAG_EMPTY = 3 };
#define FPU_TW_ALL_EMPTY 0xFFFFu
#define FPU_TW_RESET     0x5555u /* power-up value (all zero) [SDM 3A Table 12-1] */

struct x87_state {
    struct fp80 st[8];      /* physical registers R0-R7; ST(i) = R[(TOP + i) & 7] */
    u16 control;
    u16 status;
    u16 tag;
    u32 fip;                /* last instruction pointer (offset) */
    u16 fcs;                /* last instruction CS selector */
    u32 fdp;                /* last data operand offset */
    u16 fds;                /* last data operand selector */
    u16 last_opcode;        /* 11 bits [SDM 1 §8.1.9 p.218] */
    bool error_pending;     /* unmasked exception awaiting the next ESC/WAIT → #MF [i386 §11.1.5.3 p.192] */
};

/* Memory image formats for FSTENV/FLDENV/FNSAVE/FRSTOR. [SDM 1 §8.1.10 p.219, Fig 8-9..8-12] */
enum fpu_env_format {
    FPU_ENV_REAL16 = 0,   /* 14-byte env */
    FPU_ENV_REAL32,       /* 28-byte env */
    FPU_ENV_PROT16,       /* 14-byte env */
    FPU_ENV_PROT32        /* 28-byte env; + 80 bytes of registers = 108-byte FNSAVE image used by ICS-OS */
};
#define FPU_ENV16_SIZE   14
#define FPU_ENV32_SIZE   28
#define FPU_SAVE16_SIZE  94
#define FPU_SAVE32_SIZE  108

struct cpu;
struct x86_insn;

void fpu_reset(struct x87_state *fpu);          /* power-up values */
void fpu_finit(struct x87_state *fpu);          /* FNINIT: CW=037Fh SW=0 TW=FFFFh pointers=0 */
/* EM/TS/MP arbitration before an ESC or WAIT; raises #NM when required. [i386 §11.1.3-11.1.4; SDM 3A Table 2-2] */
void fpu_check_availability(struct cpu *cpu, bool is_wait);
/* Report a pending unmasked numeric error as #MF (or via the 387 ERROR# path) before executing the next ESC/WAIT. */
void fpu_check_pending_error(struct cpu *cpu);
/* Dispatch an ESC opcode D8-DF with its ModR/M byte. [SDM 2D Tables A-7..A-22] */
void fpu_exec_esc(struct cpu *cpu, struct x86_insn *insn);
enum fpu_env_format fpu_env_format_for(const struct cpu *cpu, u8 opsize);
void fpu_store_env(struct cpu *cpu, u8 seg, u32 offset, enum fpu_env_format fmt);
void fpu_load_env(struct cpu *cpu, u8 seg, u32 offset, enum fpu_env_format fmt);
void fpu_save_state(struct cpu *cpu, u8 seg, u32 offset, enum fpu_env_format fmt);    /* FNSAVE then FNINIT */
void fpu_restore_state(struct cpu *cpu, u8 seg, u32 offset, enum fpu_env_format fmt); /* FRSTOR */
u8   fpu_top(const struct x87_state *fpu);
void fpu_set_top(struct x87_state *fpu, u8 top);
enum fpu_tag fpu_tag_of(const struct fp80 *value);
void fpu_set_tag(struct x87_state *fpu, u8 phys_reg, enum fpu_tag tag);
/* Conversions between memory operand formats and fp80. [SDM 1 §4.8 p.102; Fig 8-13] */
struct fp80 fpu_from_f32(u32 bits);
struct fp80 fpu_from_f64(u64 bits);
struct fp80 fpu_from_i16(s16 v);
struct fp80 fpu_from_i32(s32 v);
struct fp80 fpu_from_i64(s64 v);
struct fp80 fpu_from_bcd80(const u8 bcd[10]);
u32  fpu_to_f32(struct cpu *cpu, struct fp80 v);
u64  fpu_to_f64(struct cpu *cpu, struct fp80 v);

#endif /* open386_CPU_FPU_H */
