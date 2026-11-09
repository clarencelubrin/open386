/* open386 — INT 13h diskette services: 00h reset, 01h status, 02h CHS read, 08h parameters, 41h EDD check (stub). */
#include "bios/bios.h"
#include "machine/machine.h"

void bios_int13_disk(struct bios *bios, struct cpu *cpu) { O386_STUB_TODO(M1); }
void bios_irq6_floppy(struct bios *bios, struct cpu *cpu) { O386_STUB_TODO(M1); }
void bios_int19_bootstrap(struct bios *bios, struct cpu *cpu) { O386_STUB_TODO(M1); }
