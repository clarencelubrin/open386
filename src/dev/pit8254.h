/*
 * open386 — 8253/8254 programmable interval timer (ports 40h-43h). Counter 0 → IRQ0, counter 2 → speaker.
 *
 * ICS-OS programs counter 0 for its scheduler tick (kernel/hardware/chips/ directory, IDT vector 20h task gate); the HLE
 * BIOS keeps the 18.2 Hz tick count in the BDA from the same IRQ.
 */
#ifndef open386_DEV_PIT8254_H
#define open386_DEV_PIT8254_H

#include "types.h"
#include "dev/irq.h"

#define PIT_FREQ_HZ      1193182u
#define PIT_PORT_CH0     0x40
#define PIT_PORT_CH1     0x41
#define PIT_PORT_CH2     0x42
#define PIT_PORT_CONTROL 0x43

enum pit_access {
    PIT_ACCESS_LATCH = 0,
    PIT_ACCESS_LO    = 1,
    PIT_ACCESS_HI    = 2,
    PIT_ACCESS_LOHI  = 3
};

struct pit_channel {
    u16  count;         // current counting element
    u16  reload;        // count register
    u16  latch;
    bool latched;
    u8   mode;          // 0-5
    enum pit_access access;
    bool bcd;
    bool write_hi_next; // LOHI sequencing
    bool read_hi_next;
    bool gate;
    bool out;
    bool null_count;
    u8   status_latch;
    bool status_latched;
    u64  last_update_cycle;
    u64  next_event_cycle;
};

struct pit8254 {
    struct pit_channel ch[3];
    struct irq_line irq0;
    void (*speaker_out)(void *ctx, bool level);
    void *speaker_ctx;
    u32  core_hz;       // virtual CPU clock used to convert cycles → PIT ticks
};

void pit_init(struct pit8254 *pit, u32 core_hz, const struct irq_line *irq0);
void pit_reset(struct pit8254 *pit);
void pit_set_speaker_callback(struct pit8254 *pit, void (*cb)(void *ctx, bool level), void *ctx);
void pit_set_gate(struct pit8254 *pit, u8 channel, bool level); /* port 61h bit 0 drives channel 2 */
bool pit_get_out(const struct pit8254 *pit, u8 channel);
u32 pit_io_read(void *ctx, u16 port, u8 size);
void pit_io_write(void *ctx, u16 port, u8 size, u32 value);
void pit_tick(struct pit8254 *pit, u64 now_cycles);              /* advance counters, raise IRQ0 edges */
u64 pit_next_deadline(const struct pit8254 *pit);

#endif /* open386_DEV_PIT8254_H */
