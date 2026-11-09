/* open386 — 8254 PIT (stub, M0). */
#include "dev/pit8254.h"

void pit_init(struct pit8254 *pit, u32 core_hz, const struct irq_line *irq0) { O386_STUB_TODO(M1); }
void pit_reset(struct pit8254 *pit) { O386_STUB_TODO(M1); }
void pit_set_speaker_callback(struct pit8254 *pit, void (*cb)(void *ctx, bool level), void *ctx) { O386_STUB_TODO(M4); }
void pit_set_gate(struct pit8254 *pit, u8 channel, bool level) { O386_STUB_TODO(M4); }
bool pit_get_out(const struct pit8254 *pit, u8 channel) { O386_STUB_TODO(M1); return false; }
u32  pit_io_read(void *ctx, u16 port, u8 size) { O386_STUB_TODO(M1); return 0xFF; }
void pit_io_write(void *ctx, u16 port, u8 size, u32 value) { O386_STUB_TODO(M1); }
void pit_tick(struct pit8254 *pit, u64 now_cycles) { O386_STUB_TODO(M1); }
u64  pit_next_deadline(const struct pit8254 *pit) { O386_STUB_TODO(M1); return ~0ull; }
