/* open386 — IRQ line helpers (stub, M0). */
#include "dev/irq.h"

void irq_line_init(struct irq_line *line, irq_set_fn set, void *ctx, u8 irq) { O386_STUB_TODO(M1); }
void irq_line_raise(const struct irq_line *line) { O386_STUB_TODO(M1); }
void irq_line_lower(const struct irq_line *line) { O386_STUB_TODO(M1); }
void irq_line_pulse(const struct irq_line *line) { O386_STUB_TODO(M1); }
