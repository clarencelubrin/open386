/*
 * Segmentation tests keyed to [i386 §5.1.1 p.92 Fig 5-3 descriptor format], [i386 §6.3.1.2 p.110 limit checking
 * incl. expand-down], [i386 §6.3.1.1 p.109 / SDM 3A Table 3-2 type codes], [i386 §14.1 p.207 real-mode loads].
 */
#include "test.h"
#include "cpu/cpu.h"
#include "cpu/segment.h"

TEST_CASE(descriptor_parse_base_fragments_and_limit_granularity) { TEST_SKIP(M2); }
TEST_CASE(descriptor_reserved_bit21_rejected) { TEST_SKIP(M2); }
TEST_CASE(system_type_codes_match_table_3_2) { TEST_SKIP(M2); }
TEST_CASE(expand_down_limit_range_with_b_bit) { TEST_SKIP(M2); }
TEST_CASE(null_selector_into_ss_faults_into_ds_defers) { TEST_SKIP(M2); }
TEST_CASE(real_mode_load_keeps_limit_and_rights) { TEST_SKIP(M1); }
TEST_CASE(accessed_bit_written_on_every_load) { TEST_SKIP(M2); }

TEST_MAIN_BEGIN("segment")
TEST_RUN(descriptor_parse_base_fragments_and_limit_granularity);
TEST_RUN(descriptor_reserved_bit21_rejected);
TEST_RUN(system_type_codes_match_table_3_2);
TEST_RUN(expand_down_limit_range_with_b_bit);
TEST_RUN(null_selector_into_ss_faults_into_ds_defers);
TEST_RUN(real_mode_load_keeps_limit_and_rights);
TEST_RUN(accessed_bit_written_on_every_load);
TEST_MAIN_END()
