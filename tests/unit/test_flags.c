/********************************************* Status Flag Tests *********************************************
 * @file test_flags.c
 * @author Lubrin, Clarence, U.
 * @details Status-flag tests keyed to [i386 App. C p.419] (status flag summary), [i386 §2.3.4.1 p.34] flag definitions,
 *          [i386 App. D p.421] condition codes, and the shift-count masking rule [i386 §14.7 item 5 p.211].
 */
#include "test.h"
#include "cpu/cpu.h"

TEST_CASE(add8_exhaustive_cf_pf_af_zf_sf_of) {
    TEST_SKIP(M1);
}
TEST_CASE(sub8_exhaustive_cf_pf_af_zf_sf_of) {
    TEST_SKIP(M1);
}
TEST_CASE(inc_dec_preserve_cf) {
    TEST_SKIP(M1);
}
TEST_CASE(logic_ops_clear_cf_of) {
    TEST_SKIP(M1);
}
TEST_CASE(shift_count_masked_to_five_bits) {
    TEST_SKIP(M1);
}
TEST_CASE(shift_count_zero_leaves_flags) {
    TEST_SKIP(M1);
}
TEST_CASE(condition_codes_match_appendix_d) {
    TEST_SKIP(M1);
}
TEST_CASE(popf_mask_iopl_only_at_cpl0_if_only_when_cpl_le_iopl) {
    TEST_SKIP(M2);
}
TEST_CASE(reserved_bit1_always_set_and_ac_id_not_writable_on_i386dx) {
    TEST_SKIP(M2);
}

TEST_MAIN_BEGIN("flags")
TEST_RUN(add8_exhaustive_cf_pf_af_zf_sf_of);
TEST_RUN(sub8_exhaustive_cf_pf_af_zf_sf_of);
TEST_RUN(inc_dec_preserve_cf);
TEST_RUN(logic_ops_clear_cf_of);
TEST_RUN(shift_count_masked_to_five_bits);
TEST_RUN(shift_count_zero_leaves_flags);
TEST_RUN(condition_codes_match_appendix_d);
TEST_RUN(popf_mask_iopl_only_at_cpl0_if_only_when_cpl_le_iopl);
TEST_RUN(reserved_bit1_always_set_and_ac_id_not_writable_on_i386dx);
TEST_MAIN_END()
