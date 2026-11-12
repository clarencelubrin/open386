/********************************************* Floppy Controller *********************************************
 * @file fdc82077.h
 * @author Lubrin, Clarence, U.
 * @details 82077AA floppy disk controller (ports 3F0h-3F7h, IRQ6, DMA channel 2), 1.44 MB drive A:.
 *          Used by GRUB (via the BIOS INT 13h path) and directly by ICS-OS (kernel/hardware/floppy/floppy.c).
 */
#ifndef open386_DEV_FDC82077_H
#define open386_DEV_FDC82077_H

#include <stdio.h>
#include "types.h"
#include "dev/irq.h"

#define FDC_PORT_SRA   0x3F0
#define FDC_PORT_SRB   0x3F1
#define FDC_PORT_DOR   0x3F2
#define FDC_PORT_TDR   0x3F3
#define FDC_PORT_MSR   0x3F4 /* read */
#define FDC_PORT_DSR   0x3F4 /* write */
#define FDC_PORT_FIFO  0x3F5
#define FDC_PORT_DIR   0x3F7 /* read: disk change */
#define FDC_PORT_CCR   0x3F7 /* write: data rate */

/* Main status register bits. */
#define FDC_MSR_DRV0_BUSY (1u << 0)
#define FDC_MSR_CB        (1u << 4) /* command busy */
#define FDC_MSR_NDMA      (1u << 5)
#define FDC_MSR_DIO       (1u << 6) /* 1 = FIFO → CPU */
#define FDC_MSR_RQM       (1u << 7)

/* Digital output register bits. */
#define FDC_DOR_DRIVE_MASK 0x03u
#define FDC_DOR_RESET_N    (1u << 2) /* 0 = held in reset */
#define FDC_DOR_DMA_EN     (1u << 3)
#define FDC_DOR_MOTOR(n)   (1u << (4 + (n)))

/* Commands (low 5 bits). */
#define FDC_CMD_READ_TRACK     0x02
#define FDC_CMD_SPECIFY        0x03
#define FDC_CMD_SENSE_DRIVE    0x04
#define FDC_CMD_WRITE_DATA     0x05
#define FDC_CMD_READ_DATA      0x06
#define FDC_CMD_RECALIBRATE    0x07
#define FDC_CMD_SENSE_INT      0x08
#define FDC_CMD_READ_ID        0x0A
#define FDC_CMD_FORMAT_TRACK   0x0D
#define FDC_CMD_SEEK           0x0F
#define FDC_CMD_VERSION        0x10
#define FDC_CMD_CONFIGURE      0x13
#define FDC_CMD_LOCK           0x14
#define FDC_CMD_DUMPREG        0x0E
#define FDC_CMD_PERPENDICULAR  0x12

enum fdc_phase {
    FDC_PHASE_IDLE = 0,
    FDC_PHASE_COMMAND,
    FDC_PHASE_EXECUTION,
    FDC_PHASE_RESULT
};

typedef struct fdc_drive {
    bool present;
    FILE *image;
    u32  image_size;
    u8   cylinders;      // 80
    u8   heads;          // 2
    u8   sectors;        // 18
    u8   current_cylinder;
    u8   current_head;
    bool motor_on;
    bool disk_changed;
    bool write_protected;
    bool seek_done;
} FDCDrive;

typedef struct dma8237 DMA8237;

typedef struct fdc82077 {
    u8 dor, msr, dsr, ccr;
    u8 st0, st1, st2, st3;
    enum fdc_phase phase;
    u8 cmd[16];
    u8 cmd_len;
    u8 cmd_expected;
    u8 result[16];
    u8 result_len;
    u8 result_pos;
    u8 selected_drive;
    u8 srt, hut, hlt;        // SPECIFY timings
    bool non_dma;
    bool reset_sense_pending; // 4 × SENSE INTERRUPT after reset
    u8   reset_sense_count;
    bool irq_pending;
    u8   sector_buffer[512];
    u64  busy_until_cycle;
    FDCDrive drives[2];
    IRQLine irq6;
    DMA8237 *dma;
    bool implied_seek, fifo_enabled;
    u8   fifo_threshold;
} FDC82077;

void fdc_init(FDC82077 *fdc, const IRQLine *irq6, DMA8237 *dma);
void fdc_reset(FDC82077 *fdc, bool hardware);
int fdc_attach_image(FDC82077 *fdc, u8 drive, const char *path, bool read_only);
void fdc_detach_image(FDC82077 *fdc, u8 drive);
u32 fdc_io_read(void *ctx, u16 port, u8 size);
void fdc_io_write(void *ctx, u16 port, u8 size, u32 value);
void fdc_tick(FDC82077 *fdc, u64 now_cycles);
u64 fdc_next_deadline(const FDC82077 *fdc);
/* Direct sector access used by the HLE BIOS INT 13h (bypasses the controller state machine). */
int fdc_read_sectors_direct(FDC82077 *fdc, u8 drive, u8 cyl, u8 head, u8 sector, u8 count, u8 *dst);
int fdc_write_sectors_direct(FDC82077 *fdc, u8 drive, u8 cyl, u8 head, u8 sector, u8 count, const u8 *src);
u32 fdc_lba_from_chs(const FDCDrive *drive, u8 cyl, u8 head, u8 sector);

#endif /* open386_DEV_FDC82077_H */
