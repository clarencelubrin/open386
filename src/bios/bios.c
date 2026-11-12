/* open386 — HLE BIOS core: ROM construction, POST, trap dispatch, BDA helpers (stub, M0). PLAN.md §6.3. */
#include "bios/bios.h"
#include "machine/machine.h"

int bios_init(BIOS *bios, Machine *m) {
    O386_STUB_TODO(M1);
    return 0;
}
void bios_build_rom(BIOS *bios) {
    O386_STUB_TODO(M1);
}
void bios_post(BIOS *bios) {
    O386_STUB_TODO(M1);
}
bool bios_is_entry_point(const BIOS *bios, u32 phys_addr) {
    O386_STUB_TODO(M1);
    return false;
}
void bios_trap(BIOS *bios, u32 phys_addr) {
    O386_STUB_TODO(M1);
}
void bios_set_disk(BIOS *bios, u8 index, const BIOSDisk *disk) {
    O386_STUB_TODO(M1);
}
void bios_unhandled(BIOS *bios, CPU *cpu, u8 vector) {
    O386_STUB_TODO(M1);
}
void bios_set_carry(CPU *cpu, bool set) {
    O386_STUB_TODO(M1);
}
void bios_set_zero(CPU *cpu, bool set) {
    O386_STUB_TODO(M1);
}
u8 bios_bda_read8(BIOS *bios, u16 offset) {
    O386_STUB_TODO(M1);
    return 0;
}
u16 bios_bda_read16(BIOS *bios, u16 offset) {
    O386_STUB_TODO(M1);
    return 0;
}
void bios_bda_write8(BIOS *bios, u16 offset, u8 value) {
    O386_STUB_TODO(M1);
}
void bios_bda_write16(BIOS *bios, u16 offset, u16 value) {
    O386_STUB_TODO(M1);
}
void bios_bda_write32(BIOS *bios, u16 offset, u32 value) {
    O386_STUB_TODO(M1);
}
