/* open386 — interactive monitor (stub, M6). */
#include "debugger/monitor.h"

void monitor_init(struct monitor *mon, struct machine *m, FILE *in, FILE *out) {
    O386_STUB_TODO(M6);
}
void monitor_attach(struct monitor *mon) {
    O386_STUB_TODO(M6);
}
void monitor_detach(struct monitor *mon) {
    O386_STUB_TODO(M6);
}
int monitor_run_command(struct monitor *mon, const char *line) {
    O386_STUB_TODO(M6);
    return 0;
}
void monitor_repl(struct monitor *mon) {
    O386_STUB_TODO(M6);
}
bool monitor_should_break(struct monitor *mon) {
    O386_STUB_TODO(M6);
    return false;
}
int monitor_add_breakpoint(struct monitor *mon, enum monitor_bp_kind kind, u32 address, u32 length) {
    O386_STUB_TODO(M6);
    return -1;
}
void monitor_remove_breakpoint(struct monitor *mon, int id) {
    O386_STUB_TODO(M6);
}
void monitor_dump_regs(struct monitor *mon) {
    O386_STUB_TODO(M6);
}
void monitor_dump_memory(struct monitor *mon, u32 linear, u32 len, u8 width) {
    O386_STUB_TODO(M6);
}
void monitor_disasm(struct monitor *mon, u32 linear, u32 count) {
    O386_STUB_TODO(M6);
}
void monitor_dump_gdt(struct monitor *mon) {
    O386_STUB_TODO(M6);
}
void monitor_dump_ldt(struct monitor *mon) {
    O386_STUB_TODO(M6);
}
void monitor_dump_idt(struct monitor *mon) {
    O386_STUB_TODO(M6);
}
void monitor_dump_tss(struct monitor *mon) {
    O386_STUB_TODO(M6);
}
void monitor_dump_page_tables(struct monitor *mon, u32 cr3, bool present_only) {
    O386_STUB_TODO(M6);
}
void monitor_dump_tlb(struct monitor *mon) {
    O386_STUB_TODO(M6);
}
void monitor_dump_devices(struct monitor *mon) {
    O386_STUB_TODO(M6);
}
