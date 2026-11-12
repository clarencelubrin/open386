/* open386 — 8259A PIC pair (stub, M0). CPU side: [i386 §9.1 p.152]. */
#include "dev/pic8259.h"

void pic_init(PICPair *pic, void (*intr_out)(void *ctx, bool level), void *ctx) {
    O386_STUB_TODO(M1);
}
void pic_reset(PICPair *pic) {
    O386_STUB_TODO(M1);
}
void pic_set_irq(PICPair *pic, u8 irq, bool level) {
    O386_STUB_TODO(M1);
}
u8 pic_acknowledge(PICPair *pic) {
    O386_STUB_TODO(M1);
    return 0;
}
bool pic_has_pending(const PICPair *pic) {
    O386_STUB_TODO(M1);
    return false;
}
u32 pic_io_read(void *ctx, u16 port, u8 size) {
    O386_STUB_TODO(M1);
    return 0xFF;
}
void pic_io_write(void *ctx, u16 port, u8 size, u32 value) {
    O386_STUB_TODO(M1);
}
int pic_highest_pending(const PIC8259 *pic) {
    O386_STUB_TODO(M1);
    return -1;
}
void pic_update_output(PICPair *pic) {
    O386_STUB_TODO(M1);
}
