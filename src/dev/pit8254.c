/********************************************* PIT 8254 *********************************************
 * @file pit8254.c
 * @author Lubrin, Clarence, U.
 * @details 8254 PIT (stub, M0).
 */
#include "dev/pit8254.h"

void pit_init(PIT8254 *pit, u32 core_hz, const IRQLine *irq0) {
    O386_STUB_TODO(M1);
}
void pit_reset(PIT8254 *pit) {
    O386_STUB_TODO(M1);
}
void pit_set_speaker_callback(PIT8254 *pit, void (*cb)(void *ctx, bool level), void *ctx) {
    O386_STUB_TODO(M4);
}
void pit_set_gate(PIT8254 *pit, u8 channel, bool level) {
    O386_STUB_TODO(M4);
}
bool pit_get_out(const PIT8254 *pit, u8 channel) {
    O386_STUB_TODO(M1);
    return false;
}
u32 pit_io_read(void *ctx, u16 port, u8 size) {
    O386_STUB_TODO(M1);
    return 0xFF;
}
void pit_io_write(void *ctx, u16 port, u8 size, u32 value) {
    O386_STUB_TODO(M1);
}
void pit_tick(PIT8254 *pit, u64 now_cycles) {
    O386_STUB_TODO(M1);
}
u64 pit_next_deadline(const PIT8254 *pit) {
    O386_STUB_TODO(M1);
    return ~0ull;
}
