/* open386 — physical address space (stub, M0). PLAN.md §6.1. */
#include "mem/memory.h"

int  mem_init(struct memory *mem, u32 ram_bytes) { O386_STUB_TODO(M1); return 0; }
void mem_destroy(struct memory *mem) { O386_STUB_TODO(M1); }
int  mem_map_rom(struct memory *mem, u32 start, const u8 *data, u32 len, const char *name) { O386_STUB_TODO(M1); return 0; }
int  mem_map_rom_alias(struct memory *mem, u32 alias_start, u32 rom_start, u32 len, const char *name) { O386_STUB_TODO(M1); return 0; }
int  mem_map_mmio(struct memory *mem, u32 start, u32 len, mmio_read_fn read, mmio_write_fn write, void *ctx,
                  const char *name) { O386_STUB_TODO(M1); return 0; }
const struct mem_region *mem_find_region(const struct memory *mem, u32 paddr) { O386_STUB_TODO(M1); return NULL; }
u8   mem_read8(struct memory *mem, u32 paddr) { O386_STUB_TODO(M1); return 0xFF; }
u16  mem_read16(struct memory *mem, u32 paddr) { O386_STUB_TODO(M1); return 0xFFFF; }
u32  mem_read32(struct memory *mem, u32 paddr) { O386_STUB_TODO(M1); return 0xFFFFFFFFu; }
void mem_write8(struct memory *mem, u32 paddr, u8 value) { O386_STUB_TODO(M1); }
void mem_write16(struct memory *mem, u32 paddr, u16 value) { O386_STUB_TODO(M1); }
void mem_write32(struct memory *mem, u32 paddr, u32 value) { O386_STUB_TODO(M1); }
u32  mem_read(struct memory *mem, u32 paddr, u8 size) { O386_STUB_TODO(M1); return 0xFFFFFFFFu; }
void mem_write(struct memory *mem, u32 paddr, u8 size, u32 value) { O386_STUB_TODO(M1); }
void mem_read_block(struct memory *mem, u32 paddr, void *dst, u32 len) { O386_STUB_TODO(M1); }
void mem_write_block(struct memory *mem, u32 paddr, const void *src, u32 len) { O386_STUB_TODO(M1); }
u8  *mem_ram_ptr(struct memory *mem, u32 paddr, u32 len) { O386_STUB_TODO(M1); return NULL; }
void mem_set_a20(struct memory *mem, bool enabled) { O386_STUB_TODO(M1); }
bool mem_get_a20(const struct memory *mem) { O386_STUB_TODO(M1); return true; }
u32  mem_apply_a20(const struct memory *mem, u32 paddr) { O386_STUB_TODO(M1); return paddr; }
