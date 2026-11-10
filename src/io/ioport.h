/********************************************* I/O Port *********************************************
 * @file ioport.h
 * @author Lubrin, Clarence, U.
 * @details 64 Ki port I/O space with per-port handler registration.
 *
 * @cite [i386 §8.1.1 p.145 I/O address space]; 
 * @cite [SDM 1 §20.3 p.435]. Unclaimed ports read all ones.
 */
#ifndef open386_IO_IOPORT_H
#define open386_IO_IOPORT_H

#include "types.h"
#include "util/log.h"
#define IO_PORT_COUNT 65536u

typedef u32  (*io_read_fn)(void *ctx, u16 port, u8 size);
typedef void (*io_write_fn)(void *ctx, u16 port, u8 size, u32 value);

typedef struct io_handler {
    io_read_fn  read;
    io_write_fn write;
    void *ctx;
    const char *name;
} IOHandler;

typedef struct iobus {
    IOHandler ports[IO_PORT_COUNT];
    u64 reads;
    u64 writes;
    u32 unclaimed_reads;
    u32 unclaimed_writes;
} IOBus;

void iobus_init(IOBus *bus);
int iobus_register(IOBus *bus, u16 base, u16 count, io_read_fn read, io_write_fn write, void *ctx,
                    const char *name);
void iobus_unregister(IOBus *bus, u16 base, u16 count);
u32 io_read(IOBus *bus, u16 port, u8 size);
void io_write(IOBus *bus, u16 port, u8 size, u32 value);
const IOHandler *iobus_lookup(const IOBus *bus, u16 port);

#endif /* open386_IO_IOPORT_H */
