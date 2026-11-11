/*
 * open386 — physical address space: RAM, BIOS ROM (with its two aliases), MMIO windows, A20 mask.
 *
 * Platform facts (PLAN.md §2.3, §6.1): 640 KiB conventional RAM, VGA window A0000h-BFFFFh, ROM F0000h-FFFFFh
 * aliased at FFFF0000h so the reset vector FFFFFFF0h [SDM 3A §12.1.4 p.3525] works, extended RAM from 100000h.
 * The 386 can emit 21-bit real-mode addresses [i386 §14.1 p.207]; the board's A20 gate masks bit 20.
 */
#ifndef open386_MEM_MEMORY_H
#define open386_MEM_MEMORY_H

#include <stdlib.h>
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
#define DEFAULT_RW_RETURN(s) ((s)==1 ? 0xFFu : ((s)==2 ? 0xFFFFu : ((s)==4 ? 0xFFFFFFFFu : 0x0)))

enum mem_region_kind {
    MEM_REGION_RAM = 0,
    MEM_REGION_ROM,
    MEM_REGION_MMIO,
    MEM_REGION_UNMAPPED
};

typedef u32  (*mmio_read_fn)(void *ctx, u32 paddr, u8 size);
typedef void (*mmio_write_fn)(void *ctx, u32 paddr, u8 size, u32 value);

typedef struct mem_region {
    enum mem_region_kind kind;
    u32  start;         // Start physical address of the memory region
    u32  length;        // Size/length of the region
    u8  *backing;       // RAM/ROM bytes
    mmio_read_fn  read;
    mmio_write_fn write;
    void *ctx;          // Context from the open836 parameters
    const char *name;   // Memory region name
} MemRegion;

typedef struct memory {
    u8  *ram;
    u32  ram_size;
    MemRegion regions[MEM_MAX_REGIONS];
    size_t region_count;
    bool a20_enabled;
    u64  reads;
    u64  writes;
    u64  unmapped_accesses;
} PhysicalMemory;

int mem_init(PhysicalMemory *mem, u32 ram_bytes);
void mem_destroy(PhysicalMemory *mem);
int mem_map_ram(PhysicalMemory *mem, u32 start, u8 *data, u32 len, const char *name);
int mem_map_rom(PhysicalMemory *mem, u32 start, const u8 *data, u32 len, const char *name);
int mem_map_rom_alias(PhysicalMemory *mem, u32 alias_start, u32 rom_start, u32 len, const char *name);
int mem_map_mmio(PhysicalMemory *mem, u32 start, u32 len, mmio_read_fn read, mmio_write_fn write, void *ctx,
                  const char *name);
const MemRegion *mem_find_region(const PhysicalMemory *mem, u32 paddr);

u8 mem_read8(PhysicalMemory *mem, u32 paddr);
u16 mem_read16(PhysicalMemory *mem, u32 paddr);
u32 mem_read32(PhysicalMemory *mem, u32 paddr);
void mem_write8(PhysicalMemory *mem, u32 paddr, u8 value);
void mem_write16(PhysicalMemory *mem, u32 paddr, u16 value);
void mem_write32(PhysicalMemory *mem, u32 paddr, u32 value);
u32 mem_read(PhysicalMemory *mem, u32 paddr, u8 size);
void mem_write(PhysicalMemory *mem, u32 paddr, u8 size, u32 value);
void mem_read_block(PhysicalMemory *mem, u32 paddr, void *dst, u32 len);
void mem_write_block(PhysicalMemory *mem, u32 paddr, const void *src, u32 len);
/* Direct pointer into RAM for `len` bytes, or NULL if the range is not plain RAM (used by DMA/BIOS fast paths). */
u8 *mem_ram_ptr(PhysicalMemory *mem, u32 paddr, u32 len);
void mem_set_a20(PhysicalMemory *mem, bool enabled);
bool mem_get_a20(const PhysicalMemory *mem);
u32 mem_apply_a20(const PhysicalMemory *mem, u32 paddr);
#endif
