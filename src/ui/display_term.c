/* open386 — curses terminal front end for VGA text mode (stub, M1; needs libncurses at build time). */
#include "ui/display.h"

static int  term_init(struct display *d, const struct config *cfg) { O386_STUB_TODO(M1); return -1; }
static void term_shutdown(struct display *d) { O386_STUB_TODO(M1); }
static void term_render_text(struct display *d, const struct vga *vga) { O386_STUB_TODO(M1); }
static void term_render_graphics(struct display *d, const struct vga *vga) { O386_STUB_TODO(M5); }
static bool term_poll_input(struct display *d, struct kbd8042 *kbd) { O386_STUB_TODO(M4); return true; }

const struct display_ops display_term_ops = {
    .name = "term",
    .init = term_init,
    .shutdown = term_shutdown,
    .render_text = term_render_text,
    .render_graphics = term_render_graphics,
    .poll_input = term_poll_input,
};
