/********************************************* Task Switching *********************************************
 * @file task.c
 * @author Lubrin, Clarence, U.
 * @details TSS and task switching.
 *
 * @cite [i386 Ch.7 p.130-144; §9.8.10 p.165; SDM 3A Ch.10 Tables 10-1/10-2].
 */
#include "cpu/cpu.h"
#include "cpu/task.h"

void task_switch(CPU *cpu, u16 new_tss_selector, const SegmentDescriptor *new_tss_desc,
                 u32 new_tss_desc_addr, enum task_switch_reason reason, bool has_error_code, u32 error_code) { O386_STUB_TODO(M3); }
void task_validate_segments(CPU *cpu, const TSS32 *tss) {
    O386_STUB_TODO(M3);
}
void task_get_privileged_stack(CPU *cpu, u8 privilege, u16 *ss_out, u32 *esp_out) {
    O386_STUB_TODO(M2);
}
bool task_io_permitted(CPU *cpu, u16 port, u8 size) {
    O386_STUB_TODO(M2);
    return false;
}
void task_save_state(CPU *cpu, u32 tss_base, bool is_32bit) {
    O386_STUB_TODO(M3);
}
void task_load_state(CPU *cpu, u32 tss_base, bool is_32bit) {
    O386_STUB_TODO(M3);
}
bool task_tss_is_32bit(const SegmentDescriptor *tss_desc) {
    O386_STUB_TODO(M3);
    return true;
}
void task_read_tss32(CPU *cpu, u32 tss_base, TSS32 *out) {
    O386_STUB_TODO(M3);
}
void task_write_tss32(CPU *cpu, u32 tss_base, const TSS32 *in) {
    O386_STUB_TODO(M3);
}
