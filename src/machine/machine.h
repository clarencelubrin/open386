/*
 * open386 — the PC/AT-style board: CPU, memory, port bus, devices, BIOS, clock and run loop. PLAN.md §6.5.
 */
#ifndef open386_MACHINE_MACHINE_H
#define open386_MACHINE_MACHINE_H

#include "types.h"
#include "util/config.h"
#include "cpu/cpu.h"
#include "mem/memory.h"
#include "io/ioport.h"
#include "dev/pic8259.h"
#include "dev/pit8254.h"
#include "dev/kbd8042.h"
#include "dev/dma8237.h"
#include "dev/fdc82077.h"
#include "dev/vga.h"
#include "dev/cmos.h"
#include "dev/speaker.h"
#include "dev/pci.h"
#include "dev/ide.h"
#include "bios/bios.h"

#define MACHINE_MAX_TIMERS      16
#define MACHINE_DEFAULT_CORE_HZ 33000000u
#define MACHINE_UI_POLL_CYCLES  200000u
#define MACHINE_PORT_POST       0x80 /* diagnostic port: writes ignored, reads return last value (delay loops) */
#define MACHINE_PORT_A20_FAST   0x92

typedef void (*machine_timer_fn)(void *ctx, u64 now_cycles);

typedef struct machine_timer {
    bool active;
    u64  deadline;
    machine_timer_fn fire;
    void *ctx;
    const char *name;
} MachineTimer;

typedef struct display Display;
typedef struct trace Trace;
typedef struct monitor Monitor;
typedef struct gdbstub GDBStub;

typedef struct machine {
    Config cfg;
    CPU    cpu;
    PhysicalMemory mem;
    IOBus  io;

    PICPair    pic;
    PIT8254     pit;
    KBD8042     kbd;
    DMA8237     dma;
    FDC82077    fdc;
    VGA         vga;
    CMOSRtc    cmos;
    PCSpeaker   speaker;
    PCIBus     pci;
    IDEChannel ide;
    BIOS        bios;
    u8 post_code;

    Display *display;
    Trace   *trace;
    Monitor *monitor;
    GDBStub *gdb;

    u64  clock;                 // virtual cycles
    u32  core_hz;
    MachineTimer timers[MACHINE_MAX_TIMERS];
    u64  next_ui_poll;
    bool running;
    bool reset_requested;
    bool shutdown_requested;
    int  exit_code;
} Machine;

int machine_create(Machine *m, const Config *cfg);
void machine_destroy(Machine *m);
void machine_reset(Machine *m);                  /* power-on: CPU reset [i386 §10.1] + devices + BIOS POST */
int machine_run(Machine *m);                    /* until shutdown; returns exit code */
u32 machine_step(Machine *m);                   /* one CPU step + device ticks */
void machine_request_reset(void *ctx);
void machine_request_shutdown(void *ctx);

/* IRQ / INTA plumbing between devices, the 8259A pair and the CPU. */
void machine_set_irq(void *ctx, u8 irq, bool level);
void machine_pic_intr_out(void *ctx, bool level);
u8 machine_intr_ack(void *ctx);
void machine_set_a20(void *ctx, bool enabled);
bool machine_code_fetch_hook(void *ctx, u32 phys_eip);  /* HLE BIOS trap */
void machine_cpu_halted(void *ctx);

/* Timer queue. */
int machine_add_timer(Machine *m, machine_timer_fn fire, void *ctx, const char *name);
void machine_arm_timer(Machine *m, int id, u64 deadline);
void machine_cancel_timer(Machine *m, int id);
void machine_process_timers(Machine *m);
u64 machine_next_deadline(const Machine *m);
u64 machine_cycles_from_ns(const Machine *m, u64 ns);
u64 machine_cycles_from_pit_ticks(const Machine *m, u64 ticks);

/* Media. */
int machine_attach_floppy(Machine *m, u8 drive, const char *path);
int machine_load_bios_rom(Machine *m, const char *path); /* real ROM instead of HLE (M6+) */

/* Misc port handlers owned by the board (80h POST, 92h fast A20). */
u32 machine_port_io_read(void *ctx, u16 port, u8 size);
void machine_port_io_write(void *ctx, u16 port, u8 size, u32 value);

#endif /* open386_MACHINE_MACHINE_H */
