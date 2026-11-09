/* open386 — INT 10h video services used by GRUB stage2: teletype 0Eh, cursor 01h/02h/03h, mode 00h, 09h (stub). */
#include "bios/bios.h"
#include "machine/machine.h"

void bios_int10_video(struct bios *bios, struct cpu *cpu) { O386_STUB_TODO(M1); }
void bios_teletype(struct bios *bios, u8 ch, u8 attr) { O386_STUB_TODO(M1); }
