/*
 * open386 — MC146818 RTC / CMOS RAM (ports 70h/71h, IRQ8). ICS-OS reads the clock (kernel/stdlib/time.c);
 * the HLE BIOS stores memory sizes and the floppy type here.
 */
#ifndef open386_DEV_CMOS_H
#define open386_DEV_CMOS_H

#include <time.h>
#include "types.h"
#include "dev/irq.h"

#define CMOS_PORT_INDEX 0x70
#define CMOS_PORT_DATA  0x71
#define CMOS_NMI_DISABLE 0x80

enum cmos_reg {
    CMOS_SECONDS = 0x00, CMOS_SECONDS_ALARM, CMOS_MINUTES, CMOS_MINUTES_ALARM, CMOS_HOURS, CMOS_HOURS_ALARM,
    CMOS_DAY_OF_WEEK, CMOS_DAY_OF_MONTH, CMOS_MONTH, CMOS_YEAR,
    CMOS_STATUS_A = 0x0A, CMOS_STATUS_B, CMOS_STATUS_C, CMOS_STATUS_D,
    CMOS_DIAGNOSTIC = 0x0E, CMOS_SHUTDOWN = 0x0F,
    CMOS_FLOPPY_TYPE = 0x10, CMOS_HD_TYPE = 0x12, CMOS_EQUIPMENT = 0x14,
    CMOS_BASE_MEM_LO = 0x15, CMOS_BASE_MEM_HI = 0x16,
    CMOS_EXT_MEM_LO = 0x17, CMOS_EXT_MEM_HI = 0x18,
    CMOS_EXT_MEM2_LO = 0x30, CMOS_EXT_MEM2_HI = 0x31,
    CMOS_CENTURY = 0x32,
    CMOS_RAM_SIZE = 128
};

#define CMOS_STATUS_B_24H    (1u << 1)
#define CMOS_STATUS_B_BINARY (1u << 2)
#define CMOS_STATUS_B_UIE    (1u << 4)
#define CMOS_STATUS_B_AIE    (1u << 5)
#define CMOS_STATUS_B_PIE    (1u << 6)
#define CMOS_STATUS_B_SET    (1u << 7)
#define CMOS_STATUS_A_UIP    (1u << 7)

typedef struct cmos_rtc {
    u8 index;
    bool nmi_disabled;
    u8 ram[CMOS_RAM_SIZE];
    time_t base_time;        // host time at reset
    u64  base_cycle;
    u32  core_hz;
    u64  next_periodic_cycle;
    IRQLine irq8;
} CMOSRtc;

void cmos_init(CMOSRtc *cmos, u32 core_hz, const IRQLine *irq8);
void cmos_reset(CMOSRtc *cmos);
void cmos_set_memory_sizes(CMOSRtc *cmos, u32 base_kb, u32 extended_kb);
void cmos_set_floppy_types(CMOSRtc *cmos, u8 drive_a, u8 drive_b);
u32 cmos_io_read(void *ctx, u16 port, u8 size);
void cmos_io_write(void *ctx, u16 port, u8 size, u32 value);
void cmos_tick(CMOSRtc *cmos, u64 now_cycles);
u8 cmos_to_bcd(u8 v);
u8 cmos_from_bcd(u8 v);

#endif /* open386_DEV_CMOS_H */
