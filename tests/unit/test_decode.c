/*
 * Decoder tests keyed to [i386 Tables 17-2/17-3/17-4 p.243-245] (ModR/M and SIB addressing forms),
 * [i386 §17.2 p.241] prefixes, and [i386 §14.7 item 6 p.211] the 15-byte limit.
 */
#include "test.h"
#include "cpu/cpu.h"
#include "cpu/exec.h"

TEST_CASE(modrm_16bit_forms_match_table_17_2) { TEST_SKIP(M1); }
TEST_CASE(modrm_32bit_forms_match_table_17_3) { TEST_SKIP(M1); }
TEST_CASE(sib_forms_match_table_17_4) { TEST_SKIP(M1); }
TEST_CASE(default_segment_is_ss_for_bp_ebp_esp_bases) { TEST_SKIP(M1); }
TEST_CASE(prefix_66_67_toggle_sizes) { TEST_SKIP(M1); }
TEST_CASE(sixteen_bytes_of_prefixes_raise_gp) { TEST_SKIP(M1); }
TEST_CASE(reserved_opcode_82_aliases_80) { TEST_SKIP(M1); }
TEST_CASE(lock_on_non_lockable_form_raises_ud) { TEST_SKIP(M1); }

TEST_MAIN_BEGIN("decode")
TEST_RUN(modrm_16bit_forms_match_table_17_2);
TEST_RUN(modrm_32bit_forms_match_table_17_3);
TEST_RUN(sib_forms_match_table_17_4);
TEST_RUN(default_segment_is_ss_for_bp_ebp_esp_bases);
TEST_RUN(prefix_66_67_toggle_sizes);
TEST_RUN(sixteen_bytes_of_prefixes_raise_gp);
TEST_RUN(reserved_opcode_82_aliases_80);
TEST_RUN(lock_on_non_lockable_form_raises_ud);
TEST_MAIN_END()
