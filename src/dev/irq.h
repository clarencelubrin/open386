/*
 * open386 — IRQ line abstraction shared by all devices (devices never touch the CPU directly).
 */
#ifndef open386_DEV_IRQ_H
#define open386_DEV_IRQ_H

#include "types.h"

typedef void (*irq_set_fn)(void *ctx, u8 irq, bool level);

struct irq_line {
    irq_set_fn set;
    void *ctx;
    u8 irq;      // 0-15 (ISA numbering through the 8259A pair)
};

void irq_line_init(struct irq_line *line, irq_set_fn set, void *ctx, u8 irq);
void irq_line_raise(const struct irq_line *line);
void irq_line_lower(const struct irq_line *line);
void irq_line_pulse(const struct irq_line *line); /* edge: raise then lower */

#endif /* open386_DEV_IRQ_H */
