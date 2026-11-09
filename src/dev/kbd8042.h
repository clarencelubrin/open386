/*
 * open386 — 8042 keyboard controller (ports 60h/64h), PS/2 keyboard (IRQ1) and PS/2 mouse (IRQ12),
 * plus the A20 gate and system-reset outputs. ICS-OS: kernel/hardware/keyboard/{keyboard,mouse}.c.
 */
#ifndef open386_DEV_KBD8042_H
#define open386_DEV_KBD8042_H

#include "types.h"
#include "dev/irq.h"

#define KBD_PORT_DATA   0x60
#define KBD_PORT_STATUS 0x64 /* read */
#define KBD_PORT_CMD    0x64 /* write */

/* Status register bits. */
#define KBD_STATUS_OBF     (1u << 0) /* output buffer full */
#define KBD_STATUS_IBF     (1u << 1) /* input buffer full */
#define KBD_STATUS_SYS     (1u << 2)
#define KBD_STATUS_CMD     (1u << 3) /* last write was a command */
#define KBD_STATUS_INHIBIT (1u << 4)
#define KBD_STATUS_AUXB    (1u << 5) /* output buffer holds mouse data */
#define KBD_STATUS_TIMEOUT (1u << 6)
#define KBD_STATUS_PARITY  (1u << 7)

/* Command byte bits (controller RAM byte 0). */
#define KBD_CMDBYTE_KBD_INT   (1u << 0)
#define KBD_CMDBYTE_AUX_INT   (1u << 1)
#define KBD_CMDBYTE_SYS       (1u << 2)
#define KBD_CMDBYTE_KBD_DIS   (1u << 4)
#define KBD_CMDBYTE_AUX_DIS   (1u << 5)
#define KBD_CMDBYTE_XLAT      (1u << 6) /* scan code set 2 → set 1 translation */

/* Controller commands written to 64h. */
#define KBD_CMD_READ_CMDBYTE  0x20
#define KBD_CMD_WRITE_CMDBYTE 0x60
#define KBD_CMD_AUX_DISABLE   0xA7
#define KBD_CMD_AUX_ENABLE    0xA8
#define KBD_CMD_AUX_TEST      0xA9
#define KBD_CMD_SELF_TEST     0xAA
#define KBD_CMD_KBD_TEST      0xAB
#define KBD_CMD_KBD_DISABLE   0xAD
#define KBD_CMD_KBD_ENABLE    0xAE
#define KBD_CMD_READ_OUTPORT  0xD0
#define KBD_CMD_WRITE_OUTPORT 0xD1 /* bit 1 = A20, bit 0 = reset (active low) */
#define KBD_CMD_WRITE_AUX     0xD4
#define KBD_CMD_PULSE_BASE    0xF0 /* F0-FF pulse output lines; FE = CPU reset */

#define KBD_QUEUE_SIZE 64

struct kbd_queue {
    u8 data[KBD_QUEUE_SIZE];
    u8 head, tail, count;
};

struct ps2_mouse {
    bool enabled;         /* data reporting enabled (F4h) */
    bool streaming;
    u8   sample_rate;
    u8   resolution;
    bool scaling_2to1;
    u8   buttons;
    s32  acc_dx, acc_dy;
    u8   pending_cmd;     /* expecting an argument byte */
};

struct kbd8042 {
    u8 status;
    u8 command_byte;
    u8 output_port;       /* bit 1 = A20 */
    u8 pending_cmd;       /* controller command awaiting its data byte, 0 if none */
    u8 output_buffer;
    bool output_is_aux;
    struct kbd_queue kbd_queue;
    struct kbd_queue aux_queue;
    bool kbd_enabled;
    bool aux_enabled;
    u8   kbd_pending_cmd; /* keyboard device command awaiting argument (e.g. EDh LEDs, F3h typematic) */
    u8   leds;
    u8   scancode_set;
    struct ps2_mouse mouse;
    struct irq_line irq1;
    struct irq_line irq12;
    void (*a20_set)(void *ctx, bool enabled);
    void (*system_reset)(void *ctx);
    void *ctx;
};

void kbd_init(struct kbd8042 *kbd, const struct irq_line *irq1, const struct irq_line *irq12,
              void (*a20_set)(void *ctx, bool enabled), void (*system_reset)(void *ctx), void *ctx);
void kbd_reset(struct kbd8042 *kbd);
u32  kbd_io_read(void *ctx, u16 port, u8 size);
void kbd_io_write(void *ctx, u16 port, u8 size, u32 value);
/* Host input: scan code set 1 bytes (make/break), mouse motion/buttons. */
void kbd_push_scancode(struct kbd8042 *kbd, u8 scancode);
void kbd_mouse_event(struct kbd8042 *kbd, s32 dx, s32 dy, u8 buttons);
void kbd_tick(struct kbd8042 *kbd, u64 now_cycles);   /* move queued bytes into the output buffer, raise IRQs */
bool kbd_has_pending_output(const struct kbd8042 *kbd);

#endif /* open386_DEV_KBD8042_H */
