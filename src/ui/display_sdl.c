/* open386 — SDL2 front end for text and graphics modes (stub, M5; compile-time optional, -Dopen386_WITH_SDL). */
#include "ui/display.h"

static int  sdl_init(struct display *d, const struct config *cfg) { O386_STUB_TODO(M5); return -1; }
static void sdl_shutdown(struct display *d) { O386_STUB_TODO(M5); }
static void sdl_render_text(struct display *d, const struct vga *vga) { O386_STUB_TODO(M5); }
static void sdl_render_graphics(struct display *d, const struct vga *vga) { O386_STUB_TODO(M5); }
static bool sdl_poll_input(struct display *d, struct kbd8042 *kbd) { O386_STUB_TODO(M5); return true; }

const struct display_ops display_sdl_ops = {
    .name = "sdl",
    .init = sdl_init,
    .shutdown = sdl_shutdown,
    .render_text = sdl_render_text,
    .render_graphics = sdl_render_graphics,
    .poll_input = sdl_poll_input,
};
