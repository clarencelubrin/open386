/* open386 — trace writer (stub, M0). PLAN.md §7. */
#include <stdarg.h>
#include "debugger/trace.h"

int  trace_open(struct trace *t, const char *path, u32 mask) { O386_STUB_TODO(M1); return 0; }
void trace_close(struct trace *t) { O386_STUB_TODO(M1); }
bool trace_enabled(const struct trace *t, u32 flag) { O386_STUB_TODO(M1); return false; }
void trace_instruction(struct trace *t, const struct cpu *cpu, const struct x86_insn *insn) { O386_STUB_TODO(M1); }
void trace_registers(struct trace *t, const struct cpu *cpu) { O386_STUB_TODO(M1); }
void trace_event(struct trace *t, const struct cpu *cpu, const char *fmt, ...) { O386_STUB_TODO(M1); }
void trace_io(struct trace *t, bool is_write, u16 port, u8 size, u32 value) { O386_STUB_TODO(M1); }
u32  trace_parse_mask(const char *spec) { O386_STUB_TODO(M1); return 0; }
