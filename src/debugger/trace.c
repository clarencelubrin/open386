/********************************************* Trace *********************************************
 * @file trace.c
 * @author Lubrin, Clarence, U.
 * @details Trace writer (stub, M0). PLAN.md §7.
 */
#include <stdarg.h>
#include "debugger/trace.h"

int trace_open(Trace *t, const char *path, u32 mask) {
    O386_STUB_TODO(M1);
    return 0;
}
void trace_close(Trace *t) {
    O386_STUB_TODO(M1);
}
bool trace_enabled(const Trace *t, u32 flag) {
    O386_STUB_TODO(M1);
    return false;
}
void trace_instruction(Trace *t, const CPU *cpu, const X86Insn *insn) {
    O386_STUB_TODO(M1);
}
void trace_registers(Trace *t, const CPU *cpu) {
    O386_STUB_TODO(M1);
}
void trace_event(Trace *t, const CPU *cpu, const char *fmt, ...) {
    O386_STUB_TODO(M1);
}
void trace_io(Trace *t, bool is_write, u16 port, u8 size, u32 value) {
    O386_STUB_TODO(M1);
}
u32 trace_parse_mask(const char *spec) {
    O386_STUB_TODO(M1);
    return 0;
}
