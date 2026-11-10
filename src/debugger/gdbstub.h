/*
 * open386 — GDB remote serial protocol stub over TCP, so `gdb -ex 'target remote :1234'` works with
 * ICS-OS's Kernel32.sym exactly as the ICS-OS Makefile's `boot-floppy-gdb` target does with QEMU.
 */
#ifndef open386_DEBUGGER_GDBSTUB_H
#define open386_DEBUGGER_GDBSTUB_H

#include "types.h"

#define GDB_DEFAULT_PORT    1234
#define GDB_PACKET_MAX      4096
#define GDB_MAX_BREAKPOINTS 64

enum gdb_stop_reason {
    GDB_STOP_NONE = 0,
    GDB_STOP_TRAP,       // SIGTRAP: breakpoint / step
    GDB_STOP_INT,        // SIGINT: ^C from GDB
    GDB_STOP_SEGV        // unrecoverable guest fault surfaced to the debugger
};

struct machine;

struct gdbstub {
    struct machine *m;
    int  listen_fd;
    int  client_fd;
    u16  port;
    bool attached;
    bool want_stop;
    bool stepping;
    bool no_ack_mode;
    char rx[GDB_PACKET_MAX];
    size_t rx_len;
    char tx[GDB_PACKET_MAX];
    u32  breakpoints[GDB_MAX_BREAKPOINTS];
    u8   bp_count;
};

int gdbstub_init(struct gdbstub *gdb, struct machine *m, u16 port);
int gdbstub_listen(struct gdbstub *gdb);
void gdbstub_close(struct gdbstub *gdb);
/* Non-blocking: handle any pending packets; returns true if the machine should stay stopped. */
bool gdbstub_poll(struct gdbstub *gdb, bool machine_stopped);
void gdbstub_notify_stop(struct gdbstub *gdb, enum gdb_stop_reason reason);
bool gdbstub_has_breakpoint(const struct gdbstub *gdb, u32 linear);
int gdbstub_handle_packet(struct gdbstub *gdb, const char *packet, size_t len);
int gdbstub_send_packet(struct gdbstub *gdb, const char *payload);

#endif /* open386_DEBUGGER_GDBSTUB_H */
