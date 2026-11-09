/* open386 — port I/O bus (stub, M0). Ref: [i386 §8.1.1 p.145]. */
#include "io/ioport.h"

void iobus_init(struct iobus *bus) { O386_STUB_TODO(M1); }
int  iobus_register(struct iobus *bus, u16 base, u16 count, io_read_fn read, io_write_fn write, void *ctx,
                    const char *name) { O386_STUB_TODO(M1); return 0; }
void iobus_unregister(struct iobus *bus, u16 base, u16 count) { O386_STUB_TODO(M1); }
u32  io_read(struct iobus *bus, u16 port, u8 size) { O386_STUB_TODO(M1); return 0xFFFFFFFFu; }
void io_write(struct iobus *bus, u16 port, u8 size, u32 value) { O386_STUB_TODO(M1); }
const struct io_handler *iobus_lookup(const struct iobus *bus, u16 port) { O386_STUB_TODO(M1); return NULL; }
