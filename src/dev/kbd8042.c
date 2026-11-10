/* open386 — 8042 keyboard controller + PS/2 devices (stub, M0). */
#include "dev/kbd8042.h"

void kbd_init(struct kbd8042 *kbd, const struct irq_line *irq1, const struct irq_line *irq12,
              void (*a20_set)(void *ctx, bool enabled), void (*system_reset)(void *ctx), void *ctx) { O386_STUB_TODO(M1); }
void kbd_reset(struct kbd8042 *kbd) {
    O386_STUB_TODO(M1);
}
u32 kbd_io_read(void *ctx, u16 port, u8 size) {
    O386_STUB_TODO(M1);
    return 0xFF;
}
void kbd_io_write(void *ctx, u16 port, u8 size, u32 value) {
    O386_STUB_TODO(M1);
}
void kbd_push_scancode(struct kbd8042 *kbd, u8 scancode) {
    O386_STUB_TODO(M4);
}
void kbd_mouse_event(struct kbd8042 *kbd, s32 dx, s32 dy, u8 buttons) {
    O386_STUB_TODO(M4);
}
void kbd_tick(struct kbd8042 *kbd, u64 now_cycles) {
    O386_STUB_TODO(M4);
}
bool kbd_has_pending_output(const struct kbd8042 *kbd) {
    O386_STUB_TODO(M4);
    return false;
}
