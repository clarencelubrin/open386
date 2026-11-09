/* open386 — display front-end selection and shared key translation (stub, M0). */
#include "ui/display.h"

int  display_create(struct display *d, enum display_kind kind, const struct config *cfg) { O386_STUB_TODO(M1); return 0; }
void display_destroy(struct display *d) { O386_STUB_TODO(M1); }
void display_render(struct display *d, const struct vga *vga) { O386_STUB_TODO(M1); }
bool display_poll(struct display *d, struct kbd8042 *kbd) { O386_STUB_TODO(M1); return true; }
int  display_key_to_scancode(int host_key, bool pressed, u8 *out, size_t out_len) { O386_STUB_TODO(M4); return 0; }
