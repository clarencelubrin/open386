/********************************************* Display *********************************************
 * @file display.c
 * @author Lubrin, Clarence, U.
 * @details Display front-end selection and shared key translation (stub, M0).
 */
#include "ui/display.h"

int display_create(Display *d, enum display_kind kind, const Config *cfg) {
    O386_STUB_TODO(M1);
    return 0;
}
void display_destroy(Display *d) {
    O386_STUB_TODO(M1);
}
void display_render(Display *d, const VGA *vga) {
    O386_STUB_TODO(M1);
}
bool display_poll(Display *d, KBD8042 *kbd) {
    O386_STUB_TODO(M1);
    return true;
}
int display_key_to_scancode(int host_key, bool pressed, u8 *out, size_t out_len) {
    O386_STUB_TODO(M4);
    return 0;
}
