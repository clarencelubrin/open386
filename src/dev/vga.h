/*
 * open386 — VGA: text mode 3 renderer, Sequencer/CRTC/Graphics/Attribute/DAC registers, planar and chain-4
 * graphics modes. Register usage by ICS-OS: kernel/hardware/vga/dexvga.c (320x200x256, 640x480x16, Mode X).
 */
#ifndef open386_DEV_VGA_H
#define open386_DEV_VGA_H

#include <stdio.h>
#include "types.h"

#define VGA_VRAM_SIZE        (256u * 1024u) /* 4 planes × 64 KiB */
#define VGA_PLANE_SIZE       (64u * 1024u)
#define VGA_TEXT_BASE        0xB8000u
#define VGA_GFX_BASE         0xA0000u

#define VGA_PORT_AC_INDEX    0x3C0
#define VGA_PORT_AC_READ     0x3C1
#define VGA_PORT_INSTAT0     0x3C2 /* read */
#define VGA_PORT_MISC_WRITE  0x3C2
#define VGA_PORT_SEQ_INDEX   0x3C4
#define VGA_PORT_SEQ_DATA    0x3C5
#define VGA_PORT_DAC_STATE   0x3C7 /* read */
#define VGA_PORT_DAC_RINDEX  0x3C7 /* write */
#define VGA_PORT_DAC_WINDEX  0x3C8
#define VGA_PORT_DAC_DATA    0x3C9
#define VGA_PORT_FEATURE_R   0x3CA
#define VGA_PORT_MISC_READ   0x3CC
#define VGA_PORT_GC_INDEX    0x3CE
#define VGA_PORT_GC_DATA     0x3CF
#define VGA_PORT_CRTC_INDEX  0x3D4 /* 3B4h in mono */
#define VGA_PORT_CRTC_DATA   0x3D5
#define VGA_PORT_INSTAT1     0x3DA /* read: retrace; also resets the AC flip-flop */
#define VGA_PORT_FEATURE_W   0x3DA

#define VGA_SEQ_REGS   5
#define VGA_CRTC_REGS  25
#define VGA_GC_REGS    9
#define VGA_AC_REGS    21

enum vga_mode_kind {
    VGA_MODE_TEXT = 0,
    VGA_MODE_PLANAR,   // 16-colour, 4 planes (640x480x16)
    VGA_MODE_CHAIN4,   // 256-colour linear (320x200x256, mode 13h)
    VGA_MODE_MODEX,    // 256-colour unchained
    VGA_MODE_CGA2,     // 2/4-colour CGA-compatible
    VGA_MODE_UNKNOWN
};

typedef struct vga {
    u8 vram[VGA_VRAM_SIZE];
    u8 misc_output;
    u8 feature_control;
    u8 seq_index;
    u8 seq[VGA_SEQ_REGS];
    u8 crtc_index;
    u8 crtc[VGA_CRTC_REGS];
    u8 gc_index;
    u8 gc[VGA_GC_REGS];
    u8 ac_index;
    u8 ac[VGA_AC_REGS];
    bool ac_flipflop;     // false = index expected
    bool ac_palette_enabled;
    u8 dac_read_index, dac_write_index, dac_sub_index, dac_state;
    u8 palette[256][3];   // 6-bit DAC values
    u8 pel_mask;
    u8 latches[4];        // graphics-controller read latches
    u32 frame_counter;
    bool in_vretrace;
    u64 last_retrace_cycle;
    enum vga_mode_kind mode;
    u16 text_cols, text_rows;
    u16 width, height;    // current graphics resolution
    u32 start_address;    // CRTC 0Ch/0Dh
    u16 cursor_pos;
    bool dirty;
} VGA;

void vga_init(VGA *vga);
void vga_reset(VGA *vga);
u32 vga_io_read(void *ctx, u16 port, u8 size);
void vga_io_write(void *ctx, u16 port, u8 size, u32 value);
u32 vga_mmio_read(void *ctx, u32 paddr, u8 size);     /* A0000h-BFFFFh with GC read modes */
void vga_mmio_write(void *ctx, u32 paddr, u8 size, u32 value); /* write modes 0-3, plane masks */
void vga_tick(VGA *vga, u64 now_cycles);        /* retrace timing for 3DAh */
void vga_update_mode(VGA *vga);                 /* derive mode kind/resolution from registers */
/* Text-mode snapshot: cells as (char, attr) pairs, `cells` must hold cols*rows*2 bytes. */
void vga_render_text(const VGA *vga, u8 *cells, u16 *cols, u16 *rows, u16 *cursor);
/* Graphics snapshot into a 32-bit XRGB framebuffer of width*height pixels. */
void vga_render_rgb(const VGA *vga, u32 *framebuffer, u16 *width, u16 *height);
void vga_dump_text(const VGA *vga, FILE *out);

#endif /* open386_DEV_VGA_H */
