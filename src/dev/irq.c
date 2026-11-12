/* open386 — IRQ line helpers (stub, M0). */
#include "dev/irq.h"

void irq_line_init(IRQLine *line, irq_set_fn set, void *ctx, u8 irq) {
    O386_STUB_TODO(M1);
}
void irq_line_raise(const IRQLine *line) {
    O386_STUB_TODO(M1);
}
void irq_line_lower(const IRQLine *line) {
    O386_STUB_TODO(M1);
}
void irq_line_pulse(const IRQLine *line) {
    O386_STUB_TODO(M1);
}
