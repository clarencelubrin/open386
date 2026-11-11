/********************************************* Memory *********************************************
 * @file memory.c
 * @details Handles memory creation, read and write operations, and memory regions.
 * @author Lubrin, Clarence, U.
 * @cite Intel Corporation. (1986). Intel 80386 programmer's reference manual. https://css.csail.mit.edu/6.858/2014/readings/i386.pdf
 * 
 * Physical Memory: 
 * - 64MiB RAM by default (configurable), little-endian accessors read8/16/32 and write8/16/32.
 * 
 * Logical Address  31                    0
 * ( SELECTOR )     [        OFFSET       ]
 * - The segment selector (from the segment register) points to the segment descriptor from the descriptor table
 * - The offset is added to the base address from the segment descriptor entry to get the LINEAR ADDRESS.
 * 
 * Linear Address   31  22 21  12 11      0
 *                  [ DIR | PAGE | OFFSET ]
 * - Refers indirectly to physical address by specifying a page table (DIR), page within the table (PAGE), offset within the page (OFFSET).
 * DIR - address of page directory entry
 * PAGE - address of page table entry
 * OFFSET - offset within the page
 * CR3 - base address of the page directory
 *  
 * Physical Address 31                    0
 *                  [    PHYSICAL ADDR.   ]
 * 
 * "FLAT" Architecture
 * - Perform flat architecture by initially loading the segment registers with selectors for descriptors that encompass the entire 32-bit linear address space
 * - Once loaded, the segment registers don't need to be changed
 * - 32-bit offsets used by 80386 instructions are adequate to address the entire linear-address space
 */
#include "mem/memory.h"
#include <string.h>

/* Initialize the PhysicalMemory struct. Requires a fresh or destroyed struct. */
int mem_init(PhysicalMemory *mem, u32 size) {
    if (!mem || size < MEM_EXTENDED_BASE) return -1;    // need at least 1 MiB of RAM
    memset(mem, 0, sizeof(*mem));                       // start with no regions, A20 off, zeroed counters
    mem->ram = calloc(1, size);                         // one buffer for all RAM; offset == physical address
    if (!mem->ram) return -1;
    mem->ram_size = size;
    // Conventional RAM stops at the VGA window so VGA MMIO and the BIOS ROM are not shadowed
    mem_map_ram(mem, 0, mem->ram, MEM_CONVENTIONAL_SIZE, "ram-low");                    // 0 - 9FFFFh
    if (size > MEM_EXTENDED_BASE)
        mem_map_ram(mem, MEM_EXTENDED_BASE, mem->ram + MEM_EXTENDED_BASE,
                    size - MEM_EXTENDED_BASE, "ram-high");                              // 100000h - end
    return 0;
}
void mem_destroy(PhysicalMemory *mem) {
    if (!mem) return;
    free(mem->ram);                         // Clean mem->data and mem->regions
    memset(mem, 0, sizeof(*mem));           // Deallocate the physical memory
}
static int region_overlaps(PhysicalMemory *mem, u32 start, u32 len, const char *name) {
    for(size_t i=0; i < mem->region_count; i++) {
        // Check if a.start < b.start + b.len and b.start < a.start + a.len
        if (mem->regions[i].start < (u64) start + len && 
            start < (u64) mem->regions[i].start + mem->regions[i].length) 
            return -1;  // There is overlap
    }
    return 0;           // There is no overlap
}
int mem_map_ram(PhysicalMemory *mem, u32 start, u8 *data, u32 len, const char *name) {
    if (mem->region_count >= MEM_MAX_REGIONS) return -1;
    if (region_overlaps(mem, start, len, name) != 0) return -1;
    MemRegion *r = &mem->regions[mem->region_count++];
    *r = (MemRegion){                       // Set the RAM memory region
        .kind = MEM_REGION_RAM,
        .start = start,
        .length = len,
        .backing = data,
        .name = name
    };
    return 0;
}
int mem_map_rom(PhysicalMemory *mem, u32 start, const u8 *data, u32 len, const char *name) {
    if (mem->region_count >= MEM_MAX_REGIONS) return -1;
    if (region_overlaps(mem, start, len, name) != 0) return -1;
    MemRegion *r = &mem->regions[mem->region_count++];
    *r = (MemRegion){                       // Set the ROM memory region
        .kind = MEM_REGION_ROM,
        .start = start,
        .length = len,
        .backing = (u8*) data,
        .name = name
    };
    return 0;
}
int mem_map_rom_alias(PhysicalMemory *mem, u32 alias_start, u32 rom_start, u32 len, const char *name) {
    const MemRegion *rom = mem_find_region(mem, rom_start);
    if (!rom || rom->kind != MEM_REGION_ROM) return -1;               // original ROM must exist
    if (region_overlaps(mem, alias_start, len, name) != 0) return -1;
    if (rom_start + len > rom->start + rom->length) return -1;        // alias must fit inside it
    if (mem->region_count >= MEM_MAX_REGIONS) return -1;

    MemRegion *r = &mem->regions[mem->region_count++];
    *r = (MemRegion){
        .kind    = MEM_REGION_ROM,
        .start   = alias_start,
        .length  = len,
        .backing = rom->backing + (rom_start - rom->start),           // share bytes, no copy
        .name    = name,
    };
    return 0;
}
int mem_map_mmio(PhysicalMemory *mem, u32 start, u32 len, mmio_read_fn read, mmio_write_fn write, void *ctx, const char *name) {
    if (mem->region_count >= MEM_MAX_REGIONS) return -1;
    if (region_overlaps(mem, start, len, name) != 0) return -1;
    if (!read || !write) return -1;         // mem_read/mem_write call both hooks unconditionally
    MemRegion *r = &mem->regions[mem->region_count++];
    *r = (MemRegion){                       // Set the MMIO memory region
        .kind = MEM_REGION_MMIO,
        .start = start,
        .length = len,
        .read = read,
        .write = write,
        .ctx = ctx,
        .name = name
    };
    return 0; 
}
/* Lookup what MemRegion does the physical memory belongs to */
const MemRegion *mem_find_region(const PhysicalMemory *mem, u32 paddr) {
    const MemRegion *r;
    for(unsigned int i=0; i<mem->region_count; i++) {
        r = &mem->regions[i];
        if(paddr - r->start < r->length)    // Check if the paddr (starting at r->start) is within the range of r->length
            return r;
    }
    return NULL;
}
/*
 * Private workers behind mem_read/mem_write. They do the lookup and the per-byte splitting but never touch
 * mem->reads/mem->writes, so one public call counts as one access however many pieces it is split into.
 * unmapped_accesses is counted here, per unmapped piece (a read32 with 3 unmapped bytes adds 3).
 */
static u32 read_access(PhysicalMemory *mem, u32 paddr, u8 size) {
    paddr = mem_apply_a20(mem, paddr);          // wrap at 1 MiB when A20 is off
    const MemRegion *r = mem_find_region(mem, paddr);
    u32 orig_addr = paddr;
    if (!r) {
        mem->unmapped_accesses++; 
        return DEFAULT_RW_RETURN(size); 
    }
    switch (r->kind) {
        case MEM_REGION_RAM:
        case MEM_REGION_ROM: {
            u32 off = paddr - r->start;         // Calculate the offset
            if (off + size > r->length ||       // Checks if it access past the end of the region
                (mem->a20_enabled == 0 && (paddr & 0xFFFFF) + size > 0x100000)) {
                u32 v = 0;                      // return value read from the memory
                for (u8 i = 0; i < size; i++) { // read per byte depending on the size (in bytes), able to read past the region
                    // If a20 is disabled, calculate the access handling 1 MiB boundary
                    v |= read_access(mem, orig_addr + i, 1) << (8 * i);     // shift by n bytes then append to the output value
                }  
                return v;
            }
            u32 v = 0;  // Access is within the same region
            for (u8 i = 0; i < size; i++)       // build the value within the same region
                v |= (u32)r->backing[off + i] << (8 * i);
            return v;   
        }
        case MEM_REGION_MMIO: {
            u32 off = paddr - r->start;         // Calculate the offset
            u32 v = 0;                          // return value read from the memory
            if (off + size > r->length) {       // Checks if it access past the end of the region
                for (u8 i = 0; i < size; i++)   // read per byte depending on the size (in bytes), able to read past the region
                    v |= read_access(mem, orig_addr + i, 1) << (8 * i);     // each byte goes to the region that owns it
                return v;
            }
            v = r->read(r->ctx, paddr, size) & DEFAULT_RW_RETURN(size);
            return v;
        }
        default: {
            mem->unmapped_accesses++;
            return DEFAULT_RW_RETURN(size);
        }
    }
}
static void write_access(PhysicalMemory *mem, u32 paddr, u8 size, u32 value) {
    paddr = mem_apply_a20(mem, paddr);                                  // wrap at 1 MiB when A20 is off
    const MemRegion *r = mem_find_region(mem, paddr);                   // Get the memory region of paddr
    if (!r) { mem->unmapped_accesses++; return; }
    switch (r->kind) {
        case MEM_REGION_RAM: {
            u32 off = paddr - r->start;
            if (off + size > r->length ||                       // straddles: split into bytes
                (mem->a20_enabled == 0 && (paddr & 0xFFFFF) + size > 0x100000)) {
                for (u8 i = 0; i < size; i++)
                    write_access(mem, paddr + i, 1, value >> (8 * i));
                return;
            }
            for (u8 i = 0; i < size; i++) 
                r->backing[off + i] = (u8)(value >> (8 * i));
            break;
        }
        case MEM_REGION_ROM:  break;                            // read-only
        case MEM_REGION_MMIO: {
            u32 off = paddr - r->start;
            if (off + size > r->length) {                       // straddles: split into bytes
                for (u8 i = 0; i < size; i++)                   // each byte goes to the region that owns it
                    write_access(mem, paddr + i, 1, value >> (8 * i));
                return;
            }
            r->write(r->ctx, paddr, size, value);
            break;
        }
        default: {
            mem->unmapped_accesses++;
            break;
        }
    }
}
/* Public entry points: validate the size and count the access exactly once. */
u32 mem_read(PhysicalMemory *mem, u32 paddr, u8 size) {
    if (size != 1 && size != 2 && size != 4) return DEFAULT_RW_RETURN(size); // Size must be 1, 2, or 4
    mem->reads++;
    return read_access(mem, paddr, size);
}
void mem_write(PhysicalMemory *mem, u32 paddr, u8 size, u32 value) {
    if (size != 1 && size != 2 && size != 4) return; // Size must be 1, 2, or 4
    mem->writes++;
    write_access(mem, paddr, size, value);
}
u8 mem_read8(PhysicalMemory *mem, u32 paddr) {
    return mem_read(mem, paddr, 1);
} 
u16 mem_read16(PhysicalMemory *mem, u32 paddr) {
    return mem_read(mem, paddr, 2);
}
u32 mem_read32(PhysicalMemory *mem, u32 paddr) {
    return mem_read(mem, paddr, 4);
}
void mem_write8(PhysicalMemory *mem, u32 paddr, u8 value) {
    mem_write(mem, paddr, 1, value);
}
void mem_write16(PhysicalMemory *mem, u32 paddr, u16 value) {
    mem_write(mem, paddr, 2, value);
}
void mem_write32(PhysicalMemory *mem, u32 paddr, u32 value) {
    mem_write(mem, paddr, 4, value);
}
/* Copies len bytes of physical memory starting at paddr. Can span more than one region */
void mem_read_block(PhysicalMemory *mem, u32 paddr, void *dst, u32 len) {
    u8 *out = dst;  // Holds the current location to be copied to
    if (len) mem->reads++;                                      // one block call = one access
    while (len) {
        u32 a = mem_apply_a20(mem, paddr);                      // Apply A20 if disabled
        const MemRegion *r = mem_find_region(mem, a);           // Get the MemRegion of the physical address
        u32 chunk = 1;                                          // Number of bytes the fast path wants to memcpy
        if (r && (r->kind == MEM_REGION_RAM || r->kind == MEM_REGION_ROM)) {
            // Process RAM or ROM memory region
            u32 left = r->length - (a - r->start);              // bytes left in this region
            chunk = len < left ? len : left;
            if (!mem->a20_enabled) {                            // don't cross a bit-20 boundary unmasked
                u32 to_mb = 0x100000u - (a & 0xFFFFFu);         // how many bytes are left from a to next 1 MiB boundary
                if (chunk > to_mb) chunk = to_mb;               // caps the copy so it stops at the next 1 MiB boundary
            }
            memcpy(out, r->backing + (a - r->start), chunk);    // copy from r->backing + offset to out
        } else {
            *out = (u8)read_access(mem, paddr, 1);              // MMIO or unmapped: go through the hooks, uncounted
        }
        out += chunk;       // Iterate out and paddr
        paddr += chunk; 
        len -= chunk;       // Decrement length
    }
}
/* Copies len bytes from src into physical memory, starting at paddr */
void mem_write_block(PhysicalMemory *mem, u32 paddr, const void *src, u32 len) {
    // src[0] goes to paddr and src[len-1] goes to paddr + len - 1
    if (len) mem->writes++;                                     // one block call = one access
    for (u32 i = 0; i < len; i++)
        write_access(mem, paddr + i, 1, ((const u8 *)src)[i]);
}
/* Direct pointer into RAM for len bytes, or NULL if the range is not entirely plain RAM. */
u8 *mem_ram_ptr(PhysicalMemory *mem, u32 paddr, u32 len) {
    paddr = mem_apply_a20(mem, paddr);
    const MemRegion *r = mem_find_region(mem, paddr);
    if (!r || r->kind != MEM_REGION_RAM) return NULL;              // ROM, MMIO or unmapped
    u32 off = paddr - r->start;
    if (len > r->length - off) return NULL;                        // runs past the end of the region
    if (!mem->a20_enabled && len > 0x100000u - (paddr & 0xFFFFFu))
        return NULL;                                               // would wrap at a 1 MiB boundary
    return r->backing + off;
}

void mem_set_a20(PhysicalMemory *mem, bool enabled) {
    mem->a20_enabled = enabled;
}
bool mem_get_a20(const PhysicalMemory *mem) {
    return mem->a20_enabled;
}
/* It applies the A20 gate to a physical address. */
u32 mem_apply_a20(const PhysicalMemory *mem, u32 paddr) {
    // When A20 is disabled, it clears bit 20 of the address. Only mask low addresses.
    if (!mem->a20_enabled && paddr < MEM_BIOS_ROM_ALIAS) return paddr & MEM_A20_MASK_OFF;
    // When A20 is enabled, it returns the address unchanged 
    return paddr;
}
