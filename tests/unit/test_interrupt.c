/*
 * Interrupt/exception tests keyed to [i386 Table 9-6 p.172] (fault/trap/abort and return address),
 * [i386 Table 9-7 p.173] (error-code presence), [i386 Fig 9-5 p.159] (frame layouts), [i386 Fig 9-7 p.161],
 * [i386 §9.6.1.3 p.160] (TF/IF handling), [SDM 3A Table 7-5 p.3385] (double-fault classes).
 */
#include "test.h"
#include "cpu/cpu.h"

TEST_CASE(error_code_presence_matches_table_9_7) { TEST_SKIP(M2); }
TEST_CASE(exception_classes_match_table_9_6) { TEST_SKIP(M1); }
TEST_CASE(real_mode_frame_is_flags_cs_ip) { TEST_SKIP(M1); }
TEST_CASE(same_level_frame_with_and_without_error_code) { TEST_SKIP(M2); }
TEST_CASE(inter_level_frame_pushes_ss_esp_from_tss) { TEST_SKIP(M2); }
TEST_CASE(v86_frame_pushes_gs_fs_ds_es) { TEST_SKIP(M5); }
TEST_CASE(interrupt_gate_clears_if_trap_gate_keeps_if_both_clear_tf) { TEST_SKIP(M2); }
TEST_CASE(int_n_from_cpl3_into_dpl0_gate_raises_gp) { TEST_SKIP(M2); }
TEST_CASE(double_fault_classes_match_table_7_5) { TEST_SKIP(M2); }
TEST_CASE(mov_ss_inhibits_interrupts_for_one_instruction) { TEST_SKIP(M1); }

TEST_MAIN_BEGIN("interrupt")
TEST_RUN(error_code_presence_matches_table_9_7);
TEST_RUN(exception_classes_match_table_9_6);
TEST_RUN(real_mode_frame_is_flags_cs_ip);
TEST_RUN(same_level_frame_with_and_without_error_code);
TEST_RUN(inter_level_frame_pushes_ss_esp_from_tss);
TEST_RUN(v86_frame_pushes_gs_fs_ds_es);
TEST_RUN(interrupt_gate_clears_if_trap_gate_keeps_if_both_clear_tf);
TEST_RUN(int_n_from_cpl3_into_dpl0_gate_raises_gp);
TEST_RUN(double_fault_classes_match_table_7_5);
TEST_RUN(mov_ss_inhibits_interrupts_for_one_instruction);
TEST_MAIN_END()
