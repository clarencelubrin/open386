/********************************************* BIOS Disk Services *********************************************
 * @file bios_disk.c
 * @author Lubrin, Clarence, U.
 * @details INT 13h diskette services: 00h reset, 01h status, 02h CHS read, 08h parameters, 41h EDD check (stub).
 */
#include "bios/bios.h"
#include "machine/machine.h"

void bios_int13_disk(BIOS *bios, CPU *cpu) {
    O386_STUB_TODO(M1);
}
void bios_irq6_floppy(BIOS *bios, CPU *cpu) {
    O386_STUB_TODO(M1);
}
void bios_int19_bootstrap(BIOS *bios, CPU *cpu) {
    O386_STUB_TODO(M1);
}
