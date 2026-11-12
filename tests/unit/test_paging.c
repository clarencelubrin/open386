/********************************************* Paging Tests *********************************************
 * @file test_paging.c
 * @author Lubrin, Clarence, U.
 * @details Paging tests keyed to [i386 §5.2 p.98-101 Fig 5-9/5-10], [i386 §6.4 p.126-128], [i386 §9.8.14 p.169 Fig 9-8],
 *          [SDM 3A §5.3 Tables 5-3/5-5/5-6], [SDM 3B §25.30 p.4153] (no WP on the 386).
 */
#include "test.h"
#include "cpu/cpu.h"

TEST_CASE(two_level_walk_produces_frame_plus_offset) {
    TEST_SKIP(M3);
}
TEST_CASE(accessed_set_on_pde_and_pte_dirty_on_write) {
    TEST_SKIP(M3);
}
TEST_CASE(not_present_raises_pf_with_p0_and_cr2) {
    TEST_SKIP(M3);
}
TEST_CASE(user_write_to_supervisor_page_raises_pf_p1_wr_us) {
    TEST_SKIP(M3);
}
TEST_CASE(supervisor_write_to_read_only_allowed_on_i386) {
    TEST_SKIP(M3);
}
TEST_CASE(reserved_bits_ignored_on_i386_fault_when_gated) {
    TEST_SKIP(M7);
}
TEST_CASE(mov_cr3_flushes_tlb) {
    TEST_SKIP(M3);
}
TEST_CASE(invlpg_flushes_single_entry_when_gated) {
    TEST_SKIP(M3);
}

TEST_MAIN_BEGIN("paging")
TEST_RUN(two_level_walk_produces_frame_plus_offset);
TEST_RUN(accessed_set_on_pde_and_pte_dirty_on_write);
TEST_RUN(not_present_raises_pf_with_p0_and_cr2);
TEST_RUN(user_write_to_supervisor_page_raises_pf_p1_wr_us);
TEST_RUN(supervisor_write_to_read_only_allowed_on_i386);
TEST_RUN(reserved_bits_ignored_on_i386_fault_when_gated);
TEST_RUN(mov_cr3_flushes_tlb);
TEST_RUN(invlpg_flushes_single_entry_when_gated);
TEST_MAIN_END()
