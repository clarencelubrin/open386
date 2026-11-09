/* open386 — HLE BIOS core: ROM construction, POST, trap dispatch, BDA helpers (stub, M0). PLAN.md §6.3. */
#include "bios/bios.h"
#include "machine/machine.h"

int  bios_init(struct bios *bios, struct machine *m) { O386_STUB_TODO(M1); return 0; }
void bios_build_rom(struct bios *bios) { O386_STUB_TODO(M1); }
void bios_post(struct bios *bios) { O386_STUB_TODO(M1); }
bool bios_is_entry_point(const struct bios *bios, u32 phys_addr) { O386_STUB_TODO(M1); return false; }
void bios_trap(struct bios *bios, u32 phys_addr) { O386_STUB_TODO(M1); }
void bios_set_disk(struct bios *bios, u8 index, const struct bios_disk *disk) { O386_STUB_TODO(M1); }
void bios_unhandled(struct bios *bios, struct cpu *cpu, u8 vector) { O386_STUB_TODO(M1); }
void bios_set_carry(struct cpu *cpu, bool set) { O386_STUB_TODO(M1); }
void bios_set_zero(struct cpu *cpu, bool set) { O386_STUB_TODO(M1); }
u8   bios_bda_read8(struct bios *bios, u16 offset) { O386_STUB_TODO(M1); return 0; }
u16  bios_bda_read16(struct bios *bios, u16 offset) { O386_STUB_TODO(M1); return 0; }
void bios_bda_write8(struct bios *bios, u16 offset, u8 value) { O386_STUB_TODO(M1); }
void bios_bda_write16(struct bios *bios, u16 offset, u16 value) { O386_STUB_TODO(M1); }
void bios_bda_write32(struct bios *bios, u16 offset, u32 value) { O386_STUB_TODO(M1); }
