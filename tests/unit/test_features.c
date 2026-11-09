/*
 * Feature-gate tests keyed to [SDM 3B §25.13 Table 25-1 p.4126] (new instructions), [SDM 3B §25.16 p.4128]
 * (AC/ID flags), [i386 §10.1 p.174-175] and [SDM 3A Table 12-1 p.3522] (reset values).
 */
#include "test.h"
#include "cpu/cpu.h"

TEST_CASE(i386dx_model_has_no_post_386_gates) {
    TEST_ASSERT((cpu_model_i386dx.features & CPUF_BIT(CPUF_CPUID)) == 0);
    TEST_ASSERT((cpu_model_i386dx.features & CPUF_BIT(CPUF_486_INSNS)) == 0);
    TEST_ASSERT((cpu_model_i386dx.features & CPUF_BIT(CPUF_CR4)) == 0);
    TEST_ASSERT((cpu_model_i386dx.eflags_writable_mask & (EFLAGS_AC | EFLAGS_ID)) == 0);
    TEST_ASSERT_EQ_U32(cpu_model_i386dx.reset_edx >> 8 & 0xFF, CPU_I386_COMPONENT_ID);
}
TEST_CASE(icsos_model_enables_exactly_what_ics_os_needs) {
    TEST_ASSERT(cpu_model_i386_icsos.features & CPUF_BIT(CPUF_CPUID));
    TEST_ASSERT(cpu_model_i386_icsos.features & CPUF_BIT(CPUF_486_INSNS));
    TEST_ASSERT(cpu_model_i386_icsos.features & CPUF_BIT(CPUF_FPU_387));
    TEST_ASSERT((cpu_model_i386_icsos.features & CPUF_BIT(CPUF_CR4)) == 0);
    TEST_ASSERT_EQ_U32(cpu_model_i386_icsos.reset_cr0, CR0_ET);
}
TEST_CASE(reset_state_matches_manuals) { TEST_SKIP(M1); }
TEST_CASE(cpuid_raises_ud_on_i386dx_and_works_on_icsos) { TEST_SKIP(M3); }
TEST_CASE(feature_override_string_parses) { TEST_SKIP(M1); }

TEST_MAIN_BEGIN("features")
TEST_RUN(i386dx_model_has_no_post_386_gates);
TEST_RUN(icsos_model_enables_exactly_what_ics_os_needs);
TEST_RUN(reset_state_matches_manuals);
TEST_RUN(cpuid_raises_ud_on_i386dx_and_works_on_icsos);
TEST_RUN(feature_override_string_parses);
TEST_MAIN_END()
