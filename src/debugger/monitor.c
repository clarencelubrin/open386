/********************************************* Monitor *********************************************
 * @file monitor.c
 * @author Lubrin, Clarence, U.
 * @details Interactive monitor (stub, M6).
 */
#include "debugger/monitor.h"

void monitor_init(Monitor *mon, Machine *m, FILE *in, FILE *out) {
    O386_STUB_TODO(M6);
}
void monitor_attach(Monitor *mon) {
    O386_STUB_TODO(M6);
}
void monitor_detach(Monitor *mon) {
    O386_STUB_TODO(M6);
}
int monitor_run_command(Monitor *mon, const char *line) {
    O386_STUB_TODO(M6);
    return 0;
}
void monitor_repl(Monitor *mon) {
    O386_STUB_TODO(M6);
}
bool monitor_should_break(Monitor *mon) {
    O386_STUB_TODO(M6);
    return false;
}
int monitor_add_breakpoint(Monitor *mon, enum monitor_bp_kind kind, u32 address, u32 length) {
    O386_STUB_TODO(M6);
    return -1;
}
void monitor_remove_breakpoint(Monitor *mon, int id) {
    O386_STUB_TODO(M6);
}
void monitor_dump_regs(Monitor *mon) {
    O386_STUB_TODO(M6);
}
void monitor_dump_memory(Monitor *mon, u32 linear, u32 len, u8 width) {
    O386_STUB_TODO(M6);
}
void monitor_disasm(Monitor *mon, u32 linear, u32 count) {
    O386_STUB_TODO(M6);
}
void monitor_dump_gdt(Monitor *mon) {
    O386_STUB_TODO(M6);
}
void monitor_dump_ldt(Monitor *mon) {
    O386_STUB_TODO(M6);
}
void monitor_dump_idt(Monitor *mon) {
    O386_STUB_TODO(M6);
}
void monitor_dump_tss(Monitor *mon) {
    O386_STUB_TODO(M6);
}
void monitor_dump_page_tables(Monitor *mon, u32 cr3, bool present_only) {
    O386_STUB_TODO(M6);
}
void monitor_dump_tlb(Monitor *mon) {
    O386_STUB_TODO(M6);
}
void monitor_dump_devices(Monitor *mon) {
    O386_STUB_TODO(M6);
}
