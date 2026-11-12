/* open386 — MC146818 RTC/CMOS (stub, M0). */
#include "dev/cmos.h"

void cmos_init(CMOSRtc *cmos, u32 core_hz, const IRQLine *irq8) {
    O386_STUB_TODO(M1);
}
void cmos_reset(CMOSRtc *cmos) {
    O386_STUB_TODO(M1);
}
void cmos_set_memory_sizes(CMOSRtc *cmos, u32 base_kb, u32 extended_kb) {
    O386_STUB_TODO(M1);
}
void cmos_set_floppy_types(CMOSRtc *cmos, u8 drive_a, u8 drive_b) {
    O386_STUB_TODO(M1);
}
u32 cmos_io_read(void *ctx, u16 port, u8 size) {
    O386_STUB_TODO(M1);
    return 0xFF;
}
void cmos_io_write(void *ctx, u16 port, u8 size, u32 value) {
    O386_STUB_TODO(M1);
}
void cmos_tick(CMOSRtc *cmos, u64 now_cycles) {
    O386_STUB_TODO(M3);
}
u8 cmos_to_bcd(u8 v) {
    O386_STUB_TODO(M1);
    return 0;
}
u8 cmos_from_bcd(u8 v) {
    O386_STUB_TODO(M1);
    return 0;
}
