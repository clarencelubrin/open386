/*
 * open386 — CPUID (IA-32 extension, gated by CPUF_CPUID).
 *
 * Ref: [SDM 1 Ch.21 p.441; §21.3 p.446 leaves]; [SDM 2A CPUID]; [SDM 3B §25.13 Table 25-1 note 2 p.4127].
 * ICS-OS queries leaves 0, 1, 80000002h-80000004h (ics-os/ics-os/kernel/hardware/hardware.c:84-121).
 */
#ifndef open386_CPU_CPUID_H
#define open386_CPU_CPUID_H

#include "types.h"
#include "cpu/features.h"

/* "GenuineIntel" as returned in EBX, EDX, ECX by leaf 0. */
#define CPUID_VENDOR_INTEL_EBX 0x756E6547u /* "Genu" */
#define CPUID_VENDOR_INTEL_EDX 0x49656E69u /* "ineI" */
#define CPUID_VENDOR_INTEL_ECX 0x6C65746Eu /* "ntel" */

/* Leaf 1 EDX feature bits (subset relevant to this project). [SDM 1 §21.3 "Feature Information"] */
#define CPUID_1_EDX_FPU  (1u << 0)
#define CPUID_1_EDX_VME  (1u << 1)
#define CPUID_1_EDX_DE   (1u << 2)
#define CPUID_1_EDX_PSE  (1u << 3)
#define CPUID_1_EDX_TSC  (1u << 4)
#define CPUID_1_EDX_MSR  (1u << 5)
#define CPUID_1_EDX_PAE  (1u << 6)
#define CPUID_1_EDX_MCE  (1u << 7)
#define CPUID_1_EDX_CX8  (1u << 8)
#define CPUID_1_EDX_APIC (1u << 9)
#define CPUID_1_EDX_SEP  (1u << 11)
#define CPUID_1_EDX_MTRR (1u << 12)
#define CPUID_1_EDX_PGE  (1u << 13)
#define CPUID_1_EDX_CMOV (1u << 15)
#define CPUID_1_EDX_MMX  (1u << 23)
#define CPUID_1_EDX_FXSR (1u << 24)
#define CPUID_1_EDX_SSE  (1u << 25)

#define CPUID_EXT_BASE   0x80000000u
#define CPUID_BRAND_0    0x80000002u
#define CPUID_BRAND_1    0x80000003u
#define CPUID_BRAND_2    0x80000004u

struct cpu;

/* Execute CPUID on the current EAX (and ECX sub-leaf) writing EAX..EDX. Caller has checked the gate. */
void cpuid_execute(struct cpu *cpu);
bool cpuid_lookup(const struct cpu_model *model, u32 leaf, struct cpuid_leaf_desc *out);
/* Build leaf 1 EAX (type/family/model/stepping) and EDX feature bits from a model's gates. */
u32  cpuid_signature_from_model(const struct cpu_model *model);
u32  cpuid_features_from_model(const struct cpu_model *model);

#endif /* open386_CPU_CPUID_H */
