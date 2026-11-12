/********************************************* CPU Features *********************************************
 * @file features.h
 * @author Lubrin, Clarence, U.
 * @details CPU models and feature gates (the IA-32 extensibility layer, PLAN.md §4).
 *
 * The core is the Intel386 of the 1986 manual. Every later feature is an opt-in gate whose
 * introduction is documented in [SDM 3B Ch.25 "Architecture Compatibility" p.4123].
 */
#ifndef open386_CPU_FEATURES_H
#define open386_CPU_FEATURES_H

#include "types.h"

enum cpu_feature {
    CPUF_FPU_387 = 0,   // 80387 present: CR0.ET=1 at reset  [i386 §10.1 Fig 10-2 p.175; §11.1.1 p.189]
    CPUF_TEST_REGS,     // MOV TR6/TR7 (386/486 only)         [i386 §10.6 p.185; SDM 3B §25.14 p.4127]
    CPUF_486_INSNS,     // BSWAP CMPXCHG XADD INVD WBINVD INVLPG [SDM 3B §25.13 p.4126]
    CPUF_CR0_486_BITS,  // CR0.NE/WP/AM/NW/CD                 [SDM 3B §25.21 p.4140]
    CPUF_AC_FLAG,       // EFLAGS.AC writable, #AC exception  [SDM 3B §25.16 p.4128; §25.25 p.4143]
    CPUF_CPUID,         // CPUID instruction                  [SDM 3B §25.13 Table 25-1 note 2 p.4127]
    CPUF_ID_FLAG,       // EFLAGS.ID writable                 [SDM 3B §25.16 p.4128]
    CPUF_CR4,           // CR4 register                       [SDM 3B §25.21 p.4140]
    CPUF_TSC,           // RDTSC                              [SDM 3B §25.13 Table 25-1]
    CPUF_MSR,           // RDMSR/WRMSR                        [SDM 3B §25.13 Table 25-1]
    CPUF_CX8,           // CMPXCHG8B                          [SDM 3B §25.13 Table 25-1]
    CPUF_PSE,           // 4 MiB pages via PDE.PS + CR4.PSE   [SDM 3B §25.22.1.3 p.4141; SDM 3A §5.3]
    CPUF_PGE,           // global pages                       [SDM 3B §25.22.1.2 p.4141]
    CPUF_PAE,           // PAE paging                         [SDM 3B §25.22.1.1 p.4141; SDM 3A §5.4]
    CPUF_WP,            // CR0.WP supervisor write protect    [SDM 3B §25.30 p.4153]
    CPUF_CMOV,          // CMOVcc / FCMOVcc (P6)              [SDM 3B §25.13]
    CPUF_MMX,           // [SDM 3B §25.5 p.4124]
    CPUF_FXSR,          // FXSAVE/FXRSTOR [SDM 1 §8.1.11 p.220]
    CPUF_SSE,           // [SDM 3B §25.6 p.4125]
    CPUF_V86_EXT,       // CR4.VME / CR4.PVI virtual interrupts [SDM 3B §23.3.2 p.4109; §23.4 p.4114]
    CPUF_RSVD_BIT_PF,   // reserved PDE/PTE bits cause #PF    [SDM 3B §25.25 p.4143] (Pentium+)
    CPUF_RSVD_BIT_GP,   // reserved CR bits cause #GP         [SDM 3B §25.25 p.4143] (Pentium+)
    CPUF_COUNT,
    CPUF_NONE = CPUF_COUNT // "no feature required" marker in opcode tables
};

#define CPUF_BIT(f) (1ull << (f))

typedef struct cpuid_leaf_desc {
    u32 leaf;
    u32 eax, ebx, ecx, edx;
} CPUIDLeafDesc;

typedef struct cpu_model {
    const char *name;
    const char *description;
    u64  features;            // bitset of CPUF_BIT()
    u32  reset_edx;           // 386: DH=3 component id, DL=stepping [i386 §10.1 Fig 10-1 p.175];
                              // later: family/model/stepping [SDM 3A §12.1.3 Fig 12-2 p.3525]
    u32  reset_cr0;           // 386: only ET may be set [i386 Fig 10-2]; P6+: 60000010H [SDM 3A §12.1.1]
    u32  cr0_writable_mask;   // PE MP EM TS PG on the 386 (ET read-only); + 486 bits when gated
    u32  cr4_writable_mask;   // 0 unless CPUF_CR4
    u32  eflags_writable_mask; // EFLAGS_I386_WRITABLE plus gated AC/VIF/VIP/ID
    u32  dr6_reset;           // FFFF0FF0H [SDM 3A Table 12-1 p.3523]
    u32  dr7_reset;           // 00000400H
    u8   phys_addr_bits;      // 32 on the 386
    u8   family;              // CPUID family (3 for 386)
    u8   model;
    u8   stepping;
    const CPUIDLeafDesc *cpuid_leaves;
    size_t cpuid_leaf_count;
} CPUModel;

extern const CPUModel cpu_model_i386dx;     /* strict 80386 (PLAN.md §4.3) */
extern const CPUModel cpu_model_i386_icsos; /* 80386 + 387 + CPUID + 486 instructions; default */
extern const CPUModel cpu_model_i486dx;     /* declared for M7 */
extern const CPUModel cpu_model_pentium;    /* declared for M7 */

const CPUModel *cpu_model_find(const char *name);
/* Apply "+feat,-feat" overrides from the command line onto a copy of `base`. Returns 0 on success. */
int cpu_model_apply_overrides(CPUModel *dst, const CPUModel *base, const char *overrides);
const char *cpu_feature_name(enum cpu_feature f);
int cpu_feature_from_name(const char *name);
void cpu_model_list(void);

typedef struct cpu CPU;
bool cpu_has_feature(const CPU *cpu, enum cpu_feature f);

#endif /* open386_CPU_FEATURES_H */
