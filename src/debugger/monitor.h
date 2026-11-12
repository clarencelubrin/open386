/********************************************* Monitor *********************************************
 * @file monitor.h
 * @author Lubrin, Clarence, U.
 * @details Interactive monitor: breakpoints, stepping, state dumps that reuse the CPU's own descriptor and
 *          page-table parsers (so a table bug is visible immediately). PLAN.md §7.
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

typedef struct monitor_breakpoint {
    bool enabled;
    enum monitor_bp_kind kind;
    u32  address;
    u32  length;
    u64  hit_count;
} MonitorBreakpoint;

typedef struct machine Machine;

typedef struct monitor {
    Machine *m;
    FILE *in;
    FILE *out;
    bool attached;        // machine stops and reads commands
    bool single_step;
    u64  step_count;
    MonitorBreakpoint bps[MONITOR_MAX_BREAKPOINTS];
    u8   bp_count;
    char line[MONITOR_LINE_MAX];
} Monitor;

void monitor_init(Monitor *mon, Machine *m, FILE *in, FILE *out);
void monitor_attach(Monitor *mon);
void monitor_detach(Monitor *mon);
int monitor_run_command(Monitor *mon, const char *line);
void monitor_repl(Monitor *mon);            /* read commands until 'c' (continue) */
bool monitor_should_break(Monitor *mon);   /* called before each instruction */
int monitor_add_breakpoint(Monitor *mon, enum monitor_bp_kind kind, u32 address, u32 length);
void monitor_remove_breakpoint(Monitor *mon, int id);

void monitor_dump_regs(Monitor *mon);
void monitor_dump_memory(Monitor *mon, u32 linear, u32 len, u8 width);
void monitor_disasm(Monitor *mon, u32 linear, u32 count);
void monitor_dump_gdt(Monitor *mon);
void monitor_dump_ldt(Monitor *mon);
void monitor_dump_idt(Monitor *mon);
void monitor_dump_tss(Monitor *mon);
void monitor_dump_page_tables(Monitor *mon, u32 cr3, bool present_only);
void monitor_dump_tlb(Monitor *mon);
void monitor_dump_devices(Monitor *mon);

#endif /* open386_DEBUGGER_MONITOR_H */
