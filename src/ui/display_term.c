/********************************************* Terminal Display *********************************************
 * @file display_term.c
 * @author Lubrin, Clarence, U.
 * @details Curses terminal front end for VGA text mode (stub, M1; needs libncurses at build time).
 */
#include "ui/display.h"

static int term_init(Display *d, const Config *cfg) {
    O386_STUB_TODO(M1);
    return -1;
}
static void term_shutdown(Display *d) {
    O386_STUB_TODO(M1);
}
static void term_render_text(Display *d, const VGA *vga) {
    O386_STUB_TODO(M1);
}
static void term_render_graphics(Display *d, const VGA *vga) {
    O386_STUB_TODO(M5);
}
static bool term_poll_input(Display *d, KBD8042 *kbd) {
    O386_STUB_TODO(M4);
    return true;
}

const DisplayOps display_term_ops = {
    .name = "term",
    .init = term_init,
    .shutdown = term_shutdown,
    .render_text = term_render_text,
    .render_graphics = term_render_graphics,
    .poll_input = term_poll_input,
};
