/* open386 — INT 16h keyboard services and the IRQ1 handler feeding the BDA buffer (stub, M0). */
#include "bios/bios.h"
#include "machine/machine.h"

void bios_int16_keyboard(BIOS *bios, CPU *cpu) {
    O386_STUB_TODO(M1);
}
void bios_irq1_keyboard(BIOS *bios, CPU *cpu) {
    O386_STUB_TODO(M1);
}
bool bios_kbd_buffer_push(BIOS *bios, u16 scancode_ascii) {
    O386_STUB_TODO(M1);
    return false;
}
bool bios_kbd_buffer_pop(BIOS *bios, u16 *out, bool peek) {
    O386_STUB_TODO(M1);
    return false;
}
