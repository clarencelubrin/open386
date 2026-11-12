/********************************************* SDL Display *********************************************
 * @file display_sdl.c
 * @author Lubrin, Clarence, U.
 * @details SDL2 front end for text and graphics modes (stub, M5; compile-time optional, -Dopen386_WITH_SDL).
 */
#include "ui/display.h"

static int sdl_init(Display *d, const Config *cfg) {
    O386_STUB_TODO(M5);
    return -1;
}
static void sdl_shutdown(Display *d) {
    O386_STUB_TODO(M5);
}
static void sdl_render_text(Display *d, const VGA *vga) {
    O386_STUB_TODO(M5);
}
static void sdl_render_graphics(Display *d, const VGA *vga) {
    O386_STUB_TODO(M5);
}
static bool sdl_poll_input(Display *d, KBD8042 *kbd) {
    O386_STUB_TODO(M5);
    return true;
}

const DisplayOps display_sdl_ops = {
    .name = "sdl",
    .init = sdl_init,
    .shutdown = sdl_shutdown,
    .render_text = sdl_render_text,
    .render_graphics = sdl_render_graphics,
    .poll_input = sdl_poll_input,
};
