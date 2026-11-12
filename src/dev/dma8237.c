/********************************************* DMA 8237 *********************************************
 * @file dma8237.c
 * @author Lubrin, Clarence, U.
 * @details 8237A DMA (stub, M0).
 */
#include "dev/dma8237.h"

void dma_init(DMA8237 *dma, PhysicalMemory *mem) {
    O386_STUB_TODO(M4);
}
void dma_reset(DMA8237 *dma) {
    O386_STUB_TODO(M4);
}
u32 dma_io_read(void *ctx, u16 port, u8 size) {
    O386_STUB_TODO(M4);
    return 0xFF;
}
void dma_io_write(void *ctx, u16 port, u8 size, u32 value) {
    O386_STUB_TODO(M4);
}
bool dma_channel_active(const DMA8237 *dma, u8 channel) {
    O386_STUB_TODO(M4);
    return false;
}
u32 dma_physical_address(const DMA8237 *dma, u8 channel) {
    O386_STUB_TODO(M4);
    return 0;
}
u32 dma_remaining_bytes(const DMA8237 *dma, u8 channel) {
    O386_STUB_TODO(M4);
    return 0;
}
u32 dma_write_memory(DMA8237 *dma, u8 channel, const u8 *src, u32 len) {
    O386_STUB_TODO(M4);
    return 0;
}
u32 dma_read_memory(DMA8237 *dma, u8 channel, u8 *dst, u32 len) {
    O386_STUB_TODO(M4);
    return 0;
}
