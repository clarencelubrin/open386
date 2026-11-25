/********************************************* Segmentation Tests *********************************************
 * @file test_segment.c
 * @author Lubrin, Clarence, U.
 * @details Segmentation tests keyed to [i386 §5.1.1 p.92 Fig 5-3 descriptor format], [i386 §6.3.1.2 p.110 limit checking
 *          incl. expand-down], [i386 §6.3.1.1 p.109 / SDM 3A Table 3-2 type codes], [i386 §14.1 p.207 real-mode loads].
 */
#include "test.h"
#include "cpu/cpu.h"
#include "cpu/segment.h"
#include "cpu_fixture.h"
TEST_CASE(descriptor_parse_base_fragments_and_limit_granularity) {
    TEST_SKIP(M2);
}
TEST_CASE(descriptor_reserved_bit21_rejected) {
    TEST_SKIP(M2);
}
TEST_CASE(system_type_codes_match_table_3_2) {
    TEST_SKIP(M2);
}
TEST_CASE(expand_down_limit_range_with_b_bit) {
    TEST_SKIP(M2);
}
TEST_CASE(null_selector_into_ss_faults_into_ds_defers) {
    TEST_SKIP(M2);
}
TEST_CASE(real_mode_load_keeps_limit_and_rights) {
    fixture_init(0);
    cpu.seg[SEG_DS].limit = 0x12345;
    cpu.seg[SEG_DS].type = 0x2;
    cpu.seg[SEG_DS].dpl = 1;
    cpu.seg[SEG_DS].valid = false;

    segment_load_real_mode(&cpu, SEG_DS, 0x1234);
    // Assert
    TEST_ASSERT_EQ_U32(cpu.seg[SEG_DS].selector, 0x1234);   // selector=0x1234
    TEST_ASSERT_EQ_U32(cpu.seg[SEG_DS].base, 0x12340);      // base=0x12340
    TEST_ASSERT_EQ_U32(cpu.seg[SEG_DS].type, 0x2);          // limit/type/dpl unchanged
    TEST_ASSERT_EQ_U32(cpu.seg[SEG_DS].dpl, 0x1); 
    TEST_ASSERT_EQ_U32(cpu.seg[SEG_DS].limit, 0x12345);
    TEST_ASSERT_EQ_U32(cpu.seg[SEG_DS].valid, true);        // valid=true
    fixture_destroy();
}
TEST_CASE(accessed_bit_written_on_every_load) {
    TEST_SKIP(M2);
    exception_wrapper(NULL, NULL);

}

TEST_MAIN_BEGIN("segment")
TEST_RUN(descriptor_parse_base_fragments_and_limit_granularity);
TEST_RUN(descriptor_reserved_bit21_rejected);
TEST_RUN(system_type_codes_match_table_3_2);
TEST_RUN(expand_down_limit_range_with_b_bit);
TEST_RUN(null_selector_into_ss_faults_into_ds_defers);
TEST_RUN(real_mode_load_keeps_limit_and_rights);
TEST_RUN(accessed_bit_written_on_every_load);
TEST_MAIN_END()
