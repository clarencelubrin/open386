/*
 * open386 — ATA/IDE primary channel (1F0h-1F7h, 3F6h, IRQ14). Optional device (PLAN.md §1.2, M7+);
 * ICS-OS has a driver in kernel/hardware/ATA/ but boots without a disk.
 */
#ifndef open386_DEV_IDE_H
#define open386_DEV_IDE_H

#include <stdio.h>
#include "types.h"
#include "dev/irq.h"

#define IDE_PRIMARY_BASE  0x1F0
#define IDE_PRIMARY_CTRL  0x3F6
#define IDE_PRIMARY_IRQ   14

enum ide_reg {
    IDE_REG_DATA = 0, IDE_REG_ERROR_FEATURES, IDE_REG_SECTOR_COUNT, IDE_REG_LBA_LO, IDE_REG_LBA_MID,
    IDE_REG_LBA_HI, IDE_REG_DRIVE_HEAD, IDE_REG_STATUS_COMMAND
};

#define IDE_STATUS_ERR  (1u << 0)
#define IDE_STATUS_DRQ  (1u << 3)
#define IDE_STATUS_DSC  (1u << 4)
#define IDE_STATUS_DRDY (1u << 6)
#define IDE_STATUS_BSY  (1u << 7)

typedef struct ide_drive {
    bool present;
    FILE *image;
    u32  sectors_total;
    u16  cylinders, heads, sectors;
} IDEDrive;

typedef struct ide_channel {
    u16 base, ctrl;
    u8  regs[8];
    u8  control;
    u8  selected;
    u8  sector_buffer[512];
    u16 buffer_pos, buffer_len;
    IDEDrive drives[2];
    IRQLine irq;
} IDEChannel;

void ide_init(IDEChannel *ide, u16 base, u16 ctrl, const IRQLine *irq);
void ide_reset(IDEChannel *ide);
int ide_attach_image(IDEChannel *ide, u8 drive, const char *path);
u32 ide_io_read(void *ctx, u16 port, u8 size);
void ide_io_write(void *ctx, u16 port, u8 size, u32 value);

#endif /* open386_DEV_IDE_H */
