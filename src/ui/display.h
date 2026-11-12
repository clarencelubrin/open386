/*
 * open386 — front-end interface: renders the VGA state and feeds host input to the 8042. PLAN.md §6.6.
 */
#ifndef open386_UI_DISPLAY_H
#define open386_UI_DISPLAY_H

#include "types.h"
#include "util/config.h"

typedef struct vga VGA;
typedef struct kbd8042 KBD8042;
typedef struct display Display;

typedef struct display_ops {
    const char *name;
    int  (*init)(Display *d, const Config *cfg);
    void (*shutdown)(Display *d);
    void (*render_text)(Display *d, const VGA *vga);
    void (*render_graphics)(Display *d, const VGA *vga);
    /* Poll host input, pushing scan codes / mouse events into the controller. Returns false on quit. */
    bool (*poll_input)(Display *d, KBD8042 *kbd);
} DisplayOps;

typedef struct display {
    const DisplayOps *ops;
    void *priv;
    bool headless;
    u32  frames;
} Display;

extern const DisplayOps display_null_ops;  /* headless */
extern const DisplayOps display_term_ops;  /* curses text console */
extern const DisplayOps display_sdl_ops;   /* SDL2 (compile-time optional) */

int display_create(Display *d, enum display_kind kind, const Config *cfg);
void display_destroy(Display *d);
void display_render(Display *d, const VGA *vga);
bool display_poll(Display *d, KBD8042 *kbd);
/* Host key → scan code set 1 translation shared by the front ends. */
int display_key_to_scancode(int host_key, bool pressed, u8 *out, size_t out_len);

#endif /* open386_UI_DISPLAY_H */
