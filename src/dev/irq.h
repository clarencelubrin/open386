/********************************************* IRQ Lines *********************************************
 * @file irq.h
 * @author Lubrin, Clarence, U.
 * @details IRQ line abstraction shared by all devices (devices never touch the CPU directly).
 */
#ifndef open386_DEV_IRQ_H
#define open386_DEV_IRQ_H

#include "types.h"

typedef void (*irq_set_fn)(void *ctx, u8 irq, bool level);

typedef struct irq_line {
    irq_set_fn set;
    void *ctx;
    u8 irq;      // 0-15 (ISA numbering through the 8259A pair)
} IRQLine;

void irq_line_init(IRQLine *line, irq_set_fn set, void *ctx, u8 irq);
void irq_line_raise(const IRQLine *line);
void irq_line_lower(const IRQLine *line);
void irq_line_pulse(const IRQLine *line); /* edge: raise then lower */

#endif /* open386_DEV_IRQ_H */
