/* open386 — headless front end: no rendering, no input; VGA text can still be dumped (stub, M0). */
#include "ui/display.h"

static int null_init(Display *d, const Config *cfg) {
    O386_STUB_TODO(M1);
    return 0;
}
static void null_shutdown(Display *d) {
    O386_STUB_TODO(M1);
}
static void null_render_text(Display *d, const VGA *vga) {
    O386_STUB_TODO(M1);
}
static void null_render_graphics(Display *d, const VGA *vga) {
    O386_STUB_TODO(M1);
}
static bool null_poll_input(Display *d, KBD8042 *kbd) {
    O386_STUB_TODO(M1);
    return true;
}

const DisplayOps display_null_ops = {
    .name = "none",
    .init = null_init,
    .shutdown = null_shutdown,
    .render_text = null_render_text,
    .render_graphics = null_render_graphics,
    .poll_input = null_poll_input,
};
