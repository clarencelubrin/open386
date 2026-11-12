/********************************************* VGA *********************************************
 * @file vga.c
 * @author Lubrin, Clarence, U.
 * @details VGA (stub, M0). Register usage: ics-os/ics-os/kernel/hardware/vga/dexvga.c.
 */
#include "dev/vga.h"

void vga_init(VGA *vga) {
    O386_STUB_TODO(M1);
}
void vga_reset(VGA *vga) {
    O386_STUB_TODO(M1);
}
u32 vga_io_read(void *ctx, u16 port, u8 size) {
    O386_STUB_TODO(M1);
    return 0xFF;
}
void vga_io_write(void *ctx, u16 port, u8 size, u32 value) {
    O386_STUB_TODO(M1);
}
u32 vga_mmio_read(void *ctx, u32 paddr, u8 size) {
    O386_STUB_TODO(M1);
    return 0xFF;
}
void vga_mmio_write(void *ctx, u32 paddr, u8 size, u32 value) {
    O386_STUB_TODO(M1);
}
void vga_tick(VGA *vga, u64 now_cycles) {
    O386_STUB_TODO(M1);
}
void vga_update_mode(VGA *vga) {
    O386_STUB_TODO(M5);
}
void vga_render_text(const VGA *vga, u8 *cells, u16 *cols, u16 *rows, u16 *cursor) {
    O386_STUB_TODO(M1);
}
void vga_render_rgb(const VGA *vga, u32 *framebuffer, u16 *width, u16 *height) {
    O386_STUB_TODO(M5);
}
void vga_dump_text(const VGA *vga, FILE *out) {
    O386_STUB_TODO(M1);
}
