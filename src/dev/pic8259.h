/*
 * open386 — 8259A programmable interrupt controller pair (master 20h/21h, slave A0h/A1h, cascade IRQ2).
 *
 * The CPU side: INTR assertion and the interrupt-acknowledge vector [i386 §9.1 p.152]. ICS-OS programs
 * ICW1-ICW4 and masks in kernel/hardware/chips/irqhandlers.c; GRUB and the BIOS use the default vectors 08h/70h.
 */
#ifndef open386_DEV_PIC8259_H
#define open386_DEV_PIC8259_H

#include "types.h"

#define PIC_MASTER_CMD  0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD   0xA0
#define PIC_SLAVE_DATA  0xA1
#define PIC_CASCADE_IRQ 2
#define PIC_BIOS_MASTER_VECTOR 0x08
#define PIC_BIOS_SLAVE_VECTOR  0x70

enum pic_init_state {
    PIC_INIT_NONE = 0,
    PIC_INIT_ICW2,
    PIC_INIT_ICW3,
    PIC_INIT_ICW4
};

struct pic8259 {
    u8 irr;                 // interrupt request register
    u8 isr;                 // in-service register
    u8 imr;                 // interrupt mask register
    u8 icw1, icw2, icw3, icw4;
    enum pic_init_state init_state;
    u8 vector_base;         // ICW2
    bool auto_eoi;          // ICW4 AEOI
    bool single_mode;       // ICW1 SNGL
    bool read_isr;          // OCW3 RR/RIS selects ISR instead of IRR
    bool special_mask_mode; // OCW3 SMM
    bool poll_mode;
    u8 priority_base;       // lowest-priority IRQ for rotation
    u8 elcr;                // edge/level per line (board register)
    u8 last_irr_lines;      // for edge detection
    bool is_master;
};

struct pic_pair {
    struct pic8259 master;
    struct pic8259 slave;
    void (*intr_out)(void *ctx, bool level); // drives the CPU INTR pin
    void *ctx;
};

void pic_init(struct pic_pair *pic, void (*intr_out)(void *ctx, bool level), void *ctx);
void pic_reset(struct pic_pair *pic);
void pic_set_irq(struct pic_pair *pic, u8 irq, bool level);   /* 0-15 */
u8 pic_acknowledge(struct pic_pair *pic);                    /* INTA: returns vector, moves IRR→ISR; spurious IRQ7/15 */
bool pic_has_pending(const struct pic_pair *pic);
u32 pic_io_read(void *ctx, u16 port, u8 size);
void pic_io_write(void *ctx, u16 port, u8 size, u32 value);
int pic_highest_pending(const struct pic8259 *pic);           /* -1 if none */
void pic_update_output(struct pic_pair *pic);

#endif /* open386_DEV_PIC8259_H */
