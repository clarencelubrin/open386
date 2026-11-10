/* open386 — ATA/IDE channel (stub, optional device, M7+). */
#include "dev/ide.h"

void ide_init(struct ide_channel *ide, u16 base, u16 ctrl, const struct irq_line *irq) {
    O386_STUB_TODO(M7);
}
void ide_reset(struct ide_channel *ide) {
    O386_STUB_TODO(M7);
}
int ide_attach_image(struct ide_channel *ide, u8 drive, const char *path) {
    O386_STUB_TODO(M7);
    return -1;
}
u32 ide_io_read(void *ctx, u16 port, u8 size) {
    O386_STUB_TODO(M7);
    return 0xFF;
}
void ide_io_write(void *ctx, u16 port, u8 size, u32 value) {
    O386_STUB_TODO(M7);
}
