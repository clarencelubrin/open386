/* open386 — 82077AA floppy controller (stub, M0). */
#include "dev/fdc82077.h"

void fdc_init(struct fdc82077 *fdc, const struct irq_line *irq6, struct dma8237 *dma) { O386_STUB_TODO(M1); }
void fdc_reset(struct fdc82077 *fdc, bool hardware) { O386_STUB_TODO(M4); }
int  fdc_attach_image(struct fdc82077 *fdc, u8 drive, const char *path, bool read_only) { O386_STUB_TODO(M1); return 0; }
void fdc_detach_image(struct fdc82077 *fdc, u8 drive) { O386_STUB_TODO(M1); }
u32  fdc_io_read(void *ctx, u16 port, u8 size) { O386_STUB_TODO(M4); return 0xFF; }
void fdc_io_write(void *ctx, u16 port, u8 size, u32 value) { O386_STUB_TODO(M4); }
void fdc_tick(struct fdc82077 *fdc, u64 now_cycles) { O386_STUB_TODO(M4); }
u64  fdc_next_deadline(const struct fdc82077 *fdc) { O386_STUB_TODO(M4); return ~0ull; }
int  fdc_read_sectors_direct(struct fdc82077 *fdc, u8 drive, u8 cyl, u8 head, u8 sector, u8 count, u8 *dst) { O386_STUB_TODO(M1); return -1; }
int  fdc_write_sectors_direct(struct fdc82077 *fdc, u8 drive, u8 cyl, u8 head, u8 sector, u8 count, const u8 *src) { O386_STUB_TODO(M1); return -1; }
u32  fdc_lba_from_chs(const struct fdc_drive *drive, u8 cyl, u8 head, u8 sector) { O386_STUB_TODO(M1); return 0; }
