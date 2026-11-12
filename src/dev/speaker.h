/*
 * open386 — PC speaker / system control port B (61h). ICS-OS: kernel/hardware/chips/speaker.c.
 */
#ifndef open386_DEV_SPEAKER_H
#define open386_DEV_SPEAKER_H

#include "types.h"

#define SPEAKER_PORT_B 0x61
#define PORTB_TIMER2_GATE  (1u << 0)
#define PORTB_SPEAKER_DATA (1u << 1)
#define PORTB_REFRESH      (1u << 4) /* toggles on reads: software delay loops poll it */
#define PORTB_TIMER2_OUT   (1u << 5)

typedef struct pit8254 PIT8254;

typedef struct pcspeaker {
    u8 port_b;
    bool pit_out;
    bool refresh_toggle;
    PIT8254 *pit;
    void (*audio_cb)(void *ctx, bool gate, bool data); // optional host audio hook
    void *audio_ctx;
} PCSpeaker;

void speaker_init(PCSpeaker *spk, PIT8254 *pit);
void speaker_reset(PCSpeaker *spk);
u32 speaker_io_read(void *ctx, u16 port, u8 size);
void speaker_io_write(void *ctx, u16 port, u8 size, u32 value);
void speaker_set_pit_out(void *ctx, bool level);

#endif /* open386_DEV_SPEAKER_H */
