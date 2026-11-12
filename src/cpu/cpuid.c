/********************************************* CPUID *********************************************
 * @file cpuid.c
 * @author Lubrin, Clarence, U.
 * @details CPUID (gated extension).
 *
 * @cite [SDM 1 Ch.21; SDM 2A CPUID].
 */
#include "cpu/cpu.h"
#include "cpu/cpuid.h"

void cpuid_execute(CPU *cpu) {
    O386_STUB_TODO(M3);
}
bool cpuid_lookup(const CPUModel *model, u32 leaf, CPUIDLeafDesc *out) {
    O386_STUB_TODO(M3);
    return false;
}
u32 cpuid_signature_from_model(const CPUModel *model) {
    O386_STUB_TODO(M3);
    return 0;
}
u32 cpuid_features_from_model(const CPUModel *model) {
    O386_STUB_TODO(M3);
    return 0;
}
