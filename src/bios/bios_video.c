/********************************************* BIOS Video Services *********************************************
 * @file bios_video.c
 * @author Lubrin, Clarence, U.
 * @details INT 10h video services used by GRUB stage2: teletype 0Eh, cursor 01h/02h/03h, mode 00h, 09h (stub).
 */
#include "bios/bios.h"
#include "machine/machine.h"

void bios_int10_video(BIOS *bios, CPU *cpu) {
    O386_STUB_TODO(M1);
}
void bios_teletype(BIOS *bios, u8 ch, u8 attr) {
    O386_STUB_TODO(M1);
}
