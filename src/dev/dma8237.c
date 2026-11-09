/* open386 — 8237A DMA (stub, M0). */
#include "dev/dma8237.h"

void dma_init(struct dma8237 *dma, struct memory *mem) { O386_STUB_TODO(M4); }
void dma_reset(struct dma8237 *dma) { O386_STUB_TODO(M4); }
u32  dma_io_read(void *ctx, u16 port, u8 size) { O386_STUB_TODO(M4); return 0xFF; }
void dma_io_write(void *ctx, u16 port, u8 size, u32 value) { O386_STUB_TODO(M4); }
bool dma_channel_active(const struct dma8237 *dma, u8 channel) { O386_STUB_TODO(M4); return false; }
u32  dma_physical_address(const struct dma8237 *dma, u8 channel) { O386_STUB_TODO(M4); return 0; }
u32  dma_remaining_bytes(const struct dma8237 *dma, u8 channel) { O386_STUB_TODO(M4); return 0; }
u32  dma_write_memory(struct dma8237 *dma, u8 channel, const u8 *src, u32 len) { O386_STUB_TODO(M4); return 0; }
u32  dma_read_memory(struct dma8237 *dma, u8 channel, u8 *dst, u32 len) { O386_STUB_TODO(M4); return 0; }
