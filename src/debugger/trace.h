/*
 * open386 — execution trace writer. Field order matches `qemu-system-i386 -d in_asm,cpu` closely enough for
 * tools/diff_trace.py to align the two streams (PLAN.md §7).
 */
#ifndef open386_DEBUGGER_TRACE_H
#define open386_DEBUGGER_TRACE_H

#include <stdio.h>
#include "types.h"

enum trace_flags {
    TRACE_CPU   = 1u << 0, /* one line per instruction */
    TRACE_REGS  = 1u << 1, /* register dump after each instruction */
    TRACE_INT   = 1u << 2, /* exceptions, interrupts, IRET */
    TRACE_IO    = 1u << 3,
    TRACE_PF    = 1u << 4, /* page faults and TLB flushes */
    TRACE_TASK  = 1u << 5,
    TRACE_BIOS  = 1u << 6,
    TRACE_DEV   = 1u << 7,
    TRACE_MODE  = 1u << 8  /* real/protected/V86 transitions, CR0/CR3 writes */
};

struct cpu;
struct x86_insn;

struct trace {
    FILE *out;
    u32  mask;
    u64  lines;
    bool owns_file;
};

int  trace_open(struct trace *t, const char *path, u32 mask);
void trace_close(struct trace *t);
bool trace_enabled(const struct trace *t, u32 flag);
void trace_instruction(struct trace *t, const struct cpu *cpu, const struct x86_insn *insn);
void trace_registers(struct trace *t, const struct cpu *cpu);
void trace_event(struct trace *t, const struct cpu *cpu, const char *fmt, ...);
void trace_io(struct trace *t, bool is_write, u16 port, u8 size, u32 value);
u32  trace_parse_mask(const char *spec); /* "cpu,int,io" → bits */

#endif /* open386_DEBUGGER_TRACE_H */
