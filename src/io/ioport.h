/*
 * open386 — 64 Ki port I/O space with per-port handler registration.
 *
 * Ref: [i386 §8.1.1 p.145 I/O address space]; [SDM 1 §20.3 p.435]. Unclaimed ports read all ones.
 */
#ifndef open386_IO_IOPORT_H
#define open386_IO_IOPORT_H

#include "types.h"

#define IO_PORT_COUNT 65536u

typedef u32  (*io_read_fn)(void *ctx, u16 port, u8 size);
typedef void (*io_write_fn)(void *ctx, u16 port, u8 size, u32 value);

struct io_handler {
    io_read_fn  read;
    io_write_fn write;
    void *ctx;
    const char *name;
};

struct iobus {
    struct io_handler ports[IO_PORT_COUNT];
    u64 reads;
    u64 writes;
    u32 unclaimed_reads;
    u32 unclaimed_writes;
};

void iobus_init(struct iobus *bus);
int  iobus_register(struct iobus *bus, u16 base, u16 count, io_read_fn read, io_write_fn write, void *ctx,
                    const char *name);
void iobus_unregister(struct iobus *bus, u16 base, u16 count);
u32  io_read(struct iobus *bus, u16 port, u8 size);
void io_write(struct iobus *bus, u16 port, u8 size, u32 value);
const struct io_handler *iobus_lookup(const struct iobus *bus, u16 port);

#endif /* open386_IO_IOPORT_H */
