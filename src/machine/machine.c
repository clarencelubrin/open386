/********************************************* Machine *********************************************
 * @file machine.c
 * @author Lubrin, Clarence, U.
 * @details Board wiring and run loop (stub, M0). PLAN.md §6.5.
 */
#include "machine/machine.h"

int machine_create(Machine *m, const Config *cfg) {
    O386_STUB_TODO(M1);
    return 0;
}
void machine_destroy(Machine *m) {
    O386_STUB_TODO(M1);
}
void machine_reset(Machine *m) {
    O386_STUB_TODO(M1);
}
int machine_run(Machine *m) {
    O386_STUB_TODO(M1);
    return 0;
}
u32 machine_step(Machine *m) {
    O386_STUB_TODO(M1);
    return 0;
}
void machine_request_reset(void *ctx) {
    O386_STUB_TODO(M1);
}
void machine_request_shutdown(void *ctx) {
    O386_STUB_TODO(M1);
}
void machine_set_irq(void *ctx, u8 irq, bool level) {
    O386_STUB_TODO(M1);
}
void machine_pic_intr_out(void *ctx, bool level) {
    O386_STUB_TODO(M1);
}
u8 machine_intr_ack(void *ctx) {
    O386_STUB_TODO(M1);
    return 0;
}
void machine_set_a20(void *ctx, bool enabled) {
    O386_STUB_TODO(M1);
}
bool machine_code_fetch_hook(void *ctx, u32 phys_eip) {
    O386_STUB_TODO(M1);
    return false;
}
void machine_cpu_halted(void *ctx) {
    O386_STUB_TODO(M1);
}
int machine_add_timer(Machine *m, machine_timer_fn fire, void *ctx, const char *name) {
    O386_STUB_TODO(M1);
    return -1;
}
void machine_arm_timer(Machine *m, int id, u64 deadline) {
    O386_STUB_TODO(M1);
}
void machine_cancel_timer(Machine *m, int id) {
    O386_STUB_TODO(M1);
}
void machine_process_timers(Machine *m) {
    O386_STUB_TODO(M1);
}
u64 machine_next_deadline(const Machine *m) {
    O386_STUB_TODO(M1);
    return ~0ull;
}
u64 machine_cycles_from_ns(const Machine *m, u64 ns) {
    O386_STUB_TODO(M1);
    return 0;
}
u64 machine_cycles_from_pit_ticks(const Machine *m, u64 ticks) {
    O386_STUB_TODO(M1);
    return 0;
}
int machine_attach_floppy(Machine *m, u8 drive, const char *path) {
    O386_STUB_TODO(M1);
    return 0;
}
int machine_load_bios_rom(Machine *m, const char *path) {
    O386_STUB_TODO(M6);
    return -1;
}
u32 machine_port_io_read(void *ctx, u16 port, u8 size) {
    O386_STUB_TODO(M1);
    return 0xFF;
}
void machine_port_io_write(void *ctx, u16 port, u8 size, u32 value) {
    O386_STUB_TODO(M1);
}
