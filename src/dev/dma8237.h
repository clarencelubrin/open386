/*
 * open386 — 8237A DMA controllers (master 00h-0Fh with page registers 80h-8Fh; slave C0h-DFh declared, unused).
 * ICS-OS floppy driver uses channel 2 (kernel/hardware/floppy/floppy.c:345-380).
 */
#ifndef open386_DEV_DMA8237_H
#define open386_DEV_DMA8237_H

#include "types.h"

#define DMA_PORT_BASE_LOW   0x00 /* channels 0-3 address/count pairs */
#define DMA_PORT_STATUS     0x08
#define DMA_PORT_COMMAND    0x08
#define DMA_PORT_REQUEST    0x09
#define DMA_PORT_SINGLE_MASK 0x0A
#define DMA_PORT_MODE       0x0B
#define DMA_PORT_FLIPFLOP   0x0C
#define DMA_PORT_MASTER_CLR 0x0D
#define DMA_PORT_CLR_MASK   0x0E
#define DMA_PORT_ALL_MASK   0x0F
#define DMA_PORT_PAGE_BASE  0x80 /* 81h=ch2, 82h=ch3, 83h=ch1, 87h=ch0 */
#define DMA_FLOPPY_CHANNEL  2

enum dma_transfer_type {
    DMA_XFER_VERIFY = 0,
    DMA_XFER_WRITE  = 1, // I/O → memory
    DMA_XFER_READ   = 2, // memory → I/O
    DMA_XFER_INVALID = 3
};

enum dma_mode_type {
    DMA_MODE_DEMAND = 0,
    DMA_MODE_SINGLE,
    DMA_MODE_BLOCK,
    DMA_MODE_CASCADE
};

struct dma_channel {
    u16 base_address;
    u16 current_address;
    u16 base_count;
    u16 current_count;
    u8  page;
    u8  mode;            // raw mode byte
    bool masked;
    bool request;
    bool terminal_count;
    bool autoinit;
    bool decrement;
};

typedef struct memory PhysicalMemory;

struct dma8237 {
    struct dma_channel ch[8];   // 0-3 master (8-bit), 4-7 slave (16-bit)
    bool flipflop[2];
    u8   command[2];
    u8   status[2];
    PhysicalMemory *mem;
};

void dma_init(struct dma8237 *dma, PhysicalMemory *mem);
void dma_reset(struct dma8237 *dma);
u32 dma_io_read(void *ctx, u16 port, u8 size);
void dma_io_write(void *ctx, u16 port, u8 size, u32 value);
bool dma_channel_active(const struct dma8237 *dma, u8 channel);
u32 dma_physical_address(const struct dma8237 *dma, u8 channel);
u32 dma_remaining_bytes(const struct dma8237 *dma, u8 channel);
/* Device→memory and memory→device transfers; return bytes moved, set terminal count when exhausted. */
u32 dma_write_memory(struct dma8237 *dma, u8 channel, const u8 *src, u32 len);
u32 dma_read_memory(struct dma8237 *dma, u8 channel, u8 *dst, u32 len);

#endif /* open386_DEV_DMA8237_H */
