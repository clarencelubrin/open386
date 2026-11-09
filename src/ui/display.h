/*
 * open386 — front-end interface: renders the VGA state and feeds host input to the 8042. PLAN.md §6.6.
 */
#ifndef open386_UI_DISPLAY_H
#define open386_UI_DISPLAY_H

#include "types.h"
#include "util/config.h"

struct vga;
struct kbd8042;
struct display;

struct display_ops {
    const char *name;
    int  (*init)(struct display *d, const struct config *cfg);
    void (*shutdown)(struct display *d);
    void (*render_text)(struct display *d, const struct vga *vga);
    void (*render_graphics)(struct display *d, const struct vga *vga);
    /* Poll host input, pushing scan codes / mouse events into the controller. Returns false on quit. */
    bool (*poll_input)(struct display *d, struct kbd8042 *kbd);
};

struct display {
    const struct display_ops *ops;
    void *priv;
    bool headless;
    u32  frames;
};

extern const struct display_ops display_null_ops;  /* headless */
extern const struct display_ops display_term_ops;  /* curses text console */
extern const struct display_ops display_sdl_ops;   /* SDL2 (compile-time optional) */

int  display_create(struct display *d, enum display_kind kind, const struct config *cfg);
void display_destroy(struct display *d);
void display_render(struct display *d, const struct vga *vga);
bool display_poll(struct display *d, struct kbd8042 *kbd);
/* Host key → scan code set 1 translation shared by the front ends. */
int  display_key_to_scancode(int host_key, bool pressed, u8 *out, size_t out_len);

#endif /* open386_UI_DISPLAY_H */
