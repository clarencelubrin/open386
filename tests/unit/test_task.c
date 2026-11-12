/********************************************* Task Switch Tests *********************************************
 * @file test_task.c
 * @author Lubrin, Clarence, U.
 * @details Task-switch tests keyed to [i386 Fig 7-1 p.131] (TSS offsets), [i386 §7.5 p.138-140] (switch steps),
 *          [i386 §7.6.1 p.141] (busy bit), [SDM 3A Table 10-2] (busy/NT/back-link per source), [i386 §9.8.10 p.165] (#TS).
 *          Mirrors the ICS-OS usage: `jmp TSS:0`, task gates for IRQ0 and #PF, manual busy-bit reset.
 */
#include "test.h"
#include "cpu/cpu.h"
#include "cpu/task.h"

TEST_CASE(tss32_struct_offsets_match_figure_7_1) {
    /* Pure layout check: available already in M0 since the struct is declared. */
    TEST_ASSERT_EQ_U32(offsetof(TSS32, cr3), TSS32_CR3);
    TEST_ASSERT_EQ_U32(offsetof(TSS32, eip), TSS32_EIP);
    TEST_ASSERT_EQ_U32(offsetof(TSS32, eflags), TSS32_EFLAGS);
    TEST_ASSERT_EQ_U32(offsetof(TSS32, es), TSS32_ES);
    TEST_ASSERT_EQ_U32(offsetof(TSS32, ldt), TSS32_LDT);
    TEST_ASSERT_EQ_U32(offsetof(TSS32, iomap_base), TSS32_IOMAP_BASE);
    TEST_ASSERT_EQ_U32(sizeof(TSS32), TSS32_SIZE);
    TEST_ASSERT_EQ_U32(sizeof(TSS16), TSS16_SIZE);
}
TEST_CASE(jmp_to_tss_clears_old_busy_sets_new_busy) {
    TEST_SKIP(M3);
}
TEST_CASE(call_to_tss_sets_nt_and_back_link) {
    TEST_SKIP(M3);
}
TEST_CASE(iret_with_nt_returns_to_back_link_task) {
    TEST_SKIP(M3);
}
TEST_CASE(jmp_to_busy_tss_raises_gp_selector) {
    TEST_SKIP(M3);
}
TEST_CASE(tss_limit_below_103_raises_ts) {
    TEST_SKIP(M3);
}
TEST_CASE(task_gate_on_page_fault_pushes_error_code_on_new_stack) {
    TEST_SKIP(M3);
}
TEST_CASE(task_switch_sets_cr0_ts_and_flushes_tlb) {
    TEST_SKIP(M3);
}

TEST_MAIN_BEGIN("task")
TEST_RUN(tss32_struct_offsets_match_figure_7_1);
TEST_RUN(jmp_to_tss_clears_old_busy_sets_new_busy);
TEST_RUN(call_to_tss_sets_nt_and_back_link);
TEST_RUN(iret_with_nt_returns_to_back_link_task);
TEST_RUN(jmp_to_busy_tss_raises_gp_selector);
TEST_RUN(tss_limit_below_103_raises_ts);
TEST_RUN(task_gate_on_page_fault_pushes_error_code_on_new_stack);
TEST_RUN(task_switch_sets_cr0_ts_and_flushes_tlb);
TEST_MAIN_END()
