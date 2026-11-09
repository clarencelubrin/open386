/*
 * open386 — physical address space: RAM, BIOS ROM (with its two aliases), MMIO windows, A20 mask.
 *
 * Platform facts (PLAN.md §2.3, §6.1): 640 KiB conventional RAM, VGA window A0000h-BFFFFh, ROM F0000h-FFFFFh
 * aliased at FFFF0000h so the reset vector FFFFFFF0h [SDM 3A §12.1.4 p.3525] works, extended RAM from 100000h.
 * The 386 can emit 21-bit real-mode addresses [i386 §14.1 p.207]; the board's A20 gate masks bit 20.
 */
#ifndef open386_MEM_MEMORY_H
#define open386_MEM_MEMORY_H

#include "types.h"

#define MEM_CONVENTIONAL_SIZE 0xA0000u
#define MEM_VGA_WINDOW_BASE   0xA0000u
#define MEM_VGA_WINDOW_SIZE   0x20000u
#define MEM_BIOS_ROM_BASE     0xF0000u
#define MEM_BIOS_ROM_SIZE     0x10000u
#define MEM_BIOS_ROM_ALIAS    0xFFFF0000u
#define MEM_EXTENDED_BASE     0x100000u
#define MEM_A20_MASK_OFF      0xFFEFFFFFu
#define MEM_MAX_REGIONS       16

enum mem_region_kind {
    MEM_REGION_RAM = 0,
    MEM_REGION_ROM,
    MEM_REGION_MMIO,
    MEM_REGION_UNMAPPED
};

typedef u32  (*mmio_read_fn)(void *ctx, u32 paddr, u8 size);
typedef void (*mmio_write_fn)(void *ctx, u32 paddr, u8 size, u32 value);

struct mem_region {
    enum mem_region_kind kind;
    u32  start;
    u32  length;
    u8  *backing;      /* RAM/ROM bytes */
    mmio_read_fn  read;
    mmio_write_fn write;
    void *ctx;
    const char *name;
};

struct memory {
    u8  *ram;
    u32  ram_size;
    struct mem_region regions[MEM_MAX_REGIONS];
    size_t region_count;
    bool a20_enabled;
    u64  reads;
    u64  writes;
    u64  unmapped_accesses;
};

int  mem_init(struct memory *mem, u32 ram_bytes);
void mem_destroy(struct memory *mem);
int  mem_map_rom(struct memory *mem, u32 start, const u8 *data, u32 len, const char *name);
int  mem_map_rom_alias(struct memory *mem, u32 alias_start, u32 rom_start, u32 len, const char *name);
int  mem_map_mmio(struct memory *mem, u32 start, u32 len, mmio_read_fn read, mmio_write_fn write, void *ctx,
                  const char *name);
const struct mem_region *mem_find_region(const struct memory *mem, u32 paddr);

u8   mem_read8(struct memory *mem, u32 paddr);
u16  mem_read16(struct memory *mem, u32 paddr);
u32  mem_read32(struct memory *mem, u32 paddr);
void mem_write8(struct memory *mem, u32 paddr, u8 value);
void mem_write16(struct memory *mem, u32 paddr, u16 value);
void mem_write32(struct memory *mem, u32 paddr, u32 value);
u32  mem_read(struct memory *mem, u32 paddr, u8 size);
void mem_write(struct memory *mem, u32 paddr, u8 size, u32 value);
void mem_read_block(struct memory *mem, u32 paddr, void *dst, u32 len);
void mem_write_block(struct memory *mem, u32 paddr, const void *src, u32 len);
/* Direct pointer into RAM for `len` bytes, or NULL if the range is not plain RAM (used by DMA/BIOS fast paths). */
u8  *mem_ram_ptr(struct memory *mem, u32 paddr, u32 len);
void mem_set_a20(struct memory *mem, bool enabled);
bool mem_get_a20(const struct memory *mem);
u32  mem_apply_a20(const struct memory *mem, u32 paddr);

#endif /* open386_MEM_MEMORY_H */
