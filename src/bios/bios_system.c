/* open386 — INT 11h/12h/15h: equipment, conventional memory, E820h/E801h/88h memory map, A20 (2401h), wait 86h (stub). */
#include "bios/bios.h"
#include "machine/machine.h"

void bios_int11_equipment(struct bios *bios, struct cpu *cpu) { O386_STUB_TODO(M1); }
void bios_int12_memsize(struct bios *bios, struct cpu *cpu) { O386_STUB_TODO(M1); }
void bios_int15_system(struct bios *bios, struct cpu *cpu) { O386_STUB_TODO(M1); }
