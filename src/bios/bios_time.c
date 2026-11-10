/* open386 — INT 1Ah time services (00h ticks, 02h RTC time) and the IRQ0 tick handler (stub, M0). */
#include "bios/bios.h"
#include "machine/machine.h"

void bios_int1a_time(struct bios *bios, struct cpu *cpu) {
    O386_STUB_TODO(M1);
}
void bios_irq0_timer(struct bios *bios, struct cpu *cpu) {
    O386_STUB_TODO(M1);
}
