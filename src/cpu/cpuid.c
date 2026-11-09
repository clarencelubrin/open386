/* open386 — CPUID (gated extension). Ref: [SDM 1 Ch.21; SDM 2A CPUID]. */
#include "cpu/cpu.h"
#include "cpu/cpuid.h"

void cpuid_execute(struct cpu *cpu) { O386_STUB_TODO(M3); }
bool cpuid_lookup(const struct cpu_model *model, u32 leaf, struct cpuid_leaf_desc *out) { O386_STUB_TODO(M3); return false; }
u32  cpuid_signature_from_model(const struct cpu_model *model) { O386_STUB_TODO(M3); return 0; }
u32  cpuid_features_from_model(const struct cpu_model *model) { O386_STUB_TODO(M3); return 0; }
