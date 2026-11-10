/* open386 — GDB remote stub (stub, M6). */
#include "debugger/gdbstub.h"

int gdbstub_init(struct gdbstub *gdb, struct machine *m, u16 port) {
    O386_STUB_TODO(M6);
    return 0;
}
int gdbstub_listen(struct gdbstub *gdb) {
    O386_STUB_TODO(M6);
    return -1;
}
void gdbstub_close(struct gdbstub *gdb) {
    O386_STUB_TODO(M6);
}
bool gdbstub_poll(struct gdbstub *gdb, bool machine_stopped) {
    O386_STUB_TODO(M6);
    return false;
}
void gdbstub_notify_stop(struct gdbstub *gdb, enum gdb_stop_reason reason) {
    O386_STUB_TODO(M6);
}
bool gdbstub_has_breakpoint(const struct gdbstub *gdb, u32 linear) {
    O386_STUB_TODO(M6);
    return false;
}
int gdbstub_handle_packet(struct gdbstub *gdb, const char *packet, size_t len) {
    O386_STUB_TODO(M6);
    return 0;
}
int gdbstub_send_packet(struct gdbstub *gdb, const char *payload) {
    O386_STUB_TODO(M6);
    return 0;
}
