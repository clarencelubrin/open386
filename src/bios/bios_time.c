/********************************************* BIOS Time Services *********************************************
 * @file bios_time.c
 * @author Lubrin, Clarence, U.
 * @details INT 1Ah time services (00h ticks, 02h RTC time) and the IRQ0 tick handler (stub, M0).
 */
#include "bios/bios.h"
#include "machine/machine.h"

void bios_int1a_time(BIOS *bios, CPU *cpu) {
    O386_STUB_TODO(M1);
}
void bios_irq0_timer(BIOS *bios, CPU *cpu) {
    O386_STUB_TODO(M1);
}
