/* open386 — port 61h / PC speaker (stub, M0). */
#include "dev/speaker.h"

void speaker_init(struct pcspeaker *spk, struct pit8254 *pit) {
    O386_STUB_TODO(M4);
}
void speaker_reset(struct pcspeaker *spk) {
    O386_STUB_TODO(M4);
}
u32 speaker_io_read(void *ctx, u16 port, u8 size) {
    O386_STUB_TODO(M4);
    return 0;
}
void speaker_io_write(void *ctx, u16 port, u8 size, u32 value) {
    O386_STUB_TODO(M4);
}
void speaker_set_pit_out(void *ctx, bool level) {
    O386_STUB_TODO(M4);
}
