/*
 * open386 — interactive monitor: breakpoints, stepping, state dumps that reuse the CPU's own descriptor and
 * page-table parsers (so a table bug is visible immediately). PLAN.md §7.
 */
#ifndef open386_DEBUGGER_MONITOR_H
#define open386_DEBUGGER_MONITOR_H

#include <stdio.h>
#include "types.h"

#define MONITOR_MAX_BREAKPOINTS 32
#define MONITOR_LINE_MAX        256

enum monitor_bp_kind {
    MON_BP_EXEC_LINEAR = 0,
    MON_BP_EXEC_PHYS,
    MON_BP_MEM_READ,
    MON_BP_MEM_WRITE,
    MON_BP_IO_READ,
    MON_BP_IO_WRITE,
    MON_BP_EXCEPTION
};

struct monitor_breakpoint {
    bool enabled;
    enum monitor_bp_kind kind;
    u32  address;
    u32  length;
    u64  hit_count;
};

struct machine;

struct monitor {
    struct machine *m;
    FILE *in;
    FILE *out;
    bool attached;        // machine stops and reads commands
    bool single_step;
    u64  step_count;
    struct monitor_breakpoint bps[MONITOR_MAX_BREAKPOINTS];
    u8   bp_count;
    char line[MONITOR_LINE_MAX];
};

void monitor_init(struct monitor *mon, struct machine *m, FILE *in, FILE *out);
void monitor_attach(struct monitor *mon);
void monitor_detach(struct monitor *mon);
int monitor_run_command(struct monitor *mon, const char *line);
void monitor_repl(struct monitor *mon);            /* read commands until 'c' (continue) */
bool monitor_should_break(struct monitor *mon);   /* called before each instruction */
int monitor_add_breakpoint(struct monitor *mon, enum monitor_bp_kind kind, u32 address, u32 length);
void monitor_remove_breakpoint(struct monitor *mon, int id);

void monitor_dump_regs(struct monitor *mon);
void monitor_dump_memory(struct monitor *mon, u32 linear, u32 len, u8 width);
void monitor_disasm(struct monitor *mon, u32 linear, u32 count);
void monitor_dump_gdt(struct monitor *mon);
void monitor_dump_ldt(struct monitor *mon);
void monitor_dump_idt(struct monitor *mon);
void monitor_dump_tss(struct monitor *mon);
void monitor_dump_page_tables(struct monitor *mon, u32 cr3, bool present_only);
void monitor_dump_tlb(struct monitor *mon);
void monitor_dump_devices(struct monitor *mon);

#endif /* open386_DEBUGGER_MONITOR_H */
