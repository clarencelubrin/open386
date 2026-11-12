/*
 * open386 — EFLAGS layout, lazy status-flag evaluation and condition codes.
 *
 * Ref: [i386 §2.3.4 p.33, Fig 2-8] EFLAGS; [i386 §4.1.1 p.85, Fig 4-1] system flags IOPL/NT/RF/VM;
 *      [i386 App. B p.417] flag cross-reference; [i386 App. C p.419] status flag summary;
 *      [i386 App. D p.421] condition codes; [SDM 1 §3.4.3 p.81, Fig 3-8] AC/VIF/VIP/ID (post-386);
 *      [SDM 2D §B.1.4.7 p.3024] tttn condition encoding.
 */
#ifndef open386_CPU_FLAGS_H
#define open386_CPU_FLAGS_H

#include "types.h"

#define EFLAGS_CF        (1u << 0)
#define EFLAGS_RSVD1     (1u << 1)  /* always 1 */
#define EFLAGS_PF        (1u << 2)
#define EFLAGS_AF        (1u << 4)
#define EFLAGS_ZF        (1u << 6)
#define EFLAGS_SF        (1u << 7)
#define EFLAGS_TF        (1u << 8)
#define EFLAGS_IF        (1u << 9)
#define EFLAGS_DF        (1u << 10)
#define EFLAGS_OF        (1u << 11)
#define EFLAGS_IOPL_SHIFT 12
#define EFLAGS_IOPL_MASK (3u << EFLAGS_IOPL_SHIFT)
#define EFLAGS_NT        (1u << 14)
#define EFLAGS_RF        (1u << 16)
#define EFLAGS_VM        (1u << 17)
/* Post-386 bits, writable only when the matching feature gate is on (PLAN.md §4.2). */
#define EFLAGS_AC        (1u << 18) /* Intel486 */
#define EFLAGS_VIF       (1u << 19) /* Pentium */
#define EFLAGS_VIP       (1u << 20) /* Pentium */
#define EFLAGS_ID        (1u << 21) /* Pentium / late Intel486 */

#define EFLAGS_STATUS_MASK  (EFLAGS_CF | EFLAGS_PF | EFLAGS_AF | EFLAGS_ZF | EFLAGS_SF | EFLAGS_OF)
#define EFLAGS_I386_WRITABLE                                                                            \
    (EFLAGS_STATUS_MASK | EFLAGS_TF | EFLAGS_IF | EFLAGS_DF | EFLAGS_IOPL_MASK | EFLAGS_NT |          \
     EFLAGS_RF | EFLAGS_VM)
#define EFLAGS_RESET_VALUE  0x00000002u /* [i386 §10.1 p.174] */

/* Operations whose status flags are computed lazily from (src1, src2, result). */
enum flag_op {
    FLAGOP_NONE = 0, // eflags holds materialised status flags
    FLAGOP_ADD,
    FLAGOP_ADC,
    FLAGOP_SUB,
    FLAGOP_SBB,
    FLAGOP_INC,      // CF preserved
    FLAGOP_DEC,      // CF preserved
    FLAGOP_NEG,
    FLAGOP_LOGIC,    // AND/OR/XOR/TEST: CF=OF=0, AF undefined
    FLAGOP_SHL,
    FLAGOP_SHR,
    FLAGOP_SAR,
    FLAGOP_SHLD,
    FLAGOP_SHRD,
    FLAGOP_ROL,      // only CF/OF affected
    FLAGOP_ROR,
    FLAGOP_RCL,
    FLAGOP_RCR,
    FLAGOP_MUL,      // CF=OF set when upper half non-zero; SF/ZF/AF/PF undefined
    FLAGOP_IMUL,
    FLAGOP_BSF_BSR,  // ZF only
    FLAGOP_BT,       // CF only
    FLAGOP_COUNT
};

typedef struct lazy_flags {
    enum flag_op op;
    u8  size;     // operand size in bytes
    u32 src1;
    u32 src2;
    u32 result;
    u32 aux;      // carry-in for ADC/SBB/RCx, shift count, etc.
} LazyFlags;

/* Condition codes (tttn) shared by Jcc, SETcc and (gated) CMOVcc. [i386 App. D p.421] */
enum x86_cond {
    COND_O = 0,
    COND_NO,
    COND_B,   // C
    COND_NB,  // NC / AE
    COND_E,   // Z
    COND_NE,  // NZ
    COND_BE,  // NA
    COND_NBE, // A
    COND_S,
    COND_NS,
    COND_P,   // PE
    COND_NP,  // PO
    COND_L,   // NGE
    COND_NL,  // GE
    COND_LE,  // NG
    COND_NLE  // G
};

typedef struct cpu CPU;

/* Read the architectural EFLAGS with lazily-computed status flags folded in. */
u32 cpu_get_eflags(CPU *cpu);
/* Write EFLAGS honouring `mask` (caller computes the mask from CPL/IOPL/mode per POPF/IRET rules). */
void cpu_set_eflags(CPU *cpu, u32 value, u32 mask);
void flags_set_lazy(CPU *cpu, enum flag_op op, u8 size, u32 src1, u32 src2, u32 result, u32 aux);
void flags_materialize(CPU *cpu);
bool flags_get(CPU *cpu, u32 flag_bit);
void flags_set(CPU *cpu, u32 flag_bit, bool value);
bool cpu_test_condition(CPU *cpu, enum x86_cond cond);
bool flags_parity_even(u8 value);
/* Mask of EFLAGS bits that POPF/IRET may change for the current CPL/IOPL/mode. [i386 POPF p.366] */
u32 flags_popf_writable_mask(const CPU *cpu, u8 opsize);
extern const char *const x86_cond_names[16];

#endif /* open386_CPU_FLAGS_H */
