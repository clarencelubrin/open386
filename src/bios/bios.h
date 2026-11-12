/*
 * open386 — high-level-emulated (HLE) BIOS. PLAN.md §6.3.
 *
 * The ROM at F0000h holds the IVT bootstrap, the reset-vector jump at FFFF0h and one stub per service whose
 * first bytes are a trap marker. When the CPU fetches an instruction at a registered entry point the machine
 * calls bios_trap(), which performs the service in C against the CPU's register image and then lets the stub's
 * IRET run. Services are those used by GRUB Legacy 0.92 stage1/stage2 and by ICS-OS through Multiboot.
 * Software-initialisation expectations: [i386 §10.2 p.175; SDM 3A §12.7 p.3528].
 */
#ifndef open386_BIOS_BIOS_H
#define open386_BIOS_BIOS_H

#include <stdio.h>
#include "types.h"

#define BIOS_ROM_BASE       0xF0000u
#define BIOS_ROM_SIZE       0x10000u
#define BIOS_ROM_SEGMENT    0xF000u
#define BIOS_RESET_OFFSET   0xFFF0u
#define BIOS_IVT_BASE       0x00000u
#define BIOS_BDA_BASE       0x00400u
#define BIOS_EBDA_SEGMENT   0x9FC0u
#define BIOS_BOOT_SEGMENT   0x0000u
#define BIOS_BOOT_OFFSET    0x7C00u
#define BIOS_BOOT_SIGNATURE 0xAA55u
#define BIOS_TICKS_PER_DAY  0x1800B0u

/* BIOS data area offsets (from 0040:0000). */
enum bda_offset {
    BDA_COM_PORTS       = 0x00,
    BDA_LPT_PORTS       = 0x08,
    BDA_EBDA_SEGMENT    = 0x0E,
    BDA_EQUIPMENT       = 0x10,
    BDA_MEMORY_KB       = 0x13,
    BDA_KBD_FLAGS1      = 0x17,
    BDA_KBD_FLAGS2      = 0x18,
    BDA_KBD_BUF_HEAD    = 0x1A,
    BDA_KBD_BUF_TAIL    = 0x1C,
    BDA_KBD_BUFFER      = 0x1E, // 32 bytes
    BDA_FLOPPY_RECAL    = 0x3E,
    BDA_FLOPPY_MOTOR    = 0x3F,
    BDA_FLOPPY_TIMEOUT  = 0x40,
    BDA_FLOPPY_STATUS   = 0x41,
    BDA_VIDEO_MODE      = 0x49,
    BDA_VIDEO_COLS      = 0x4A,
    BDA_VIDEO_PAGE_SIZE = 0x4C,
    BDA_VIDEO_PAGE_OFF  = 0x4E,
    BDA_CURSOR_POS      = 0x50, // 8 pages × 2 bytes
    BDA_CURSOR_SHAPE    = 0x60,
    BDA_VIDEO_PAGE      = 0x62,
    BDA_CRTC_BASE       = 0x63,
    BDA_TIMER_TICKS     = 0x6C,
    BDA_TIMER_OVERFLOW  = 0x70,
    BDA_BREAK_FLAG      = 0x71,
    BDA_RESET_FLAG      = 0x72,
    BDA_VIDEO_ROWS      = 0x84,
    BDA_CHAR_HEIGHT     = 0x85,
    BDA_KBD_FLAGS3      = 0x96
};

enum bios_vector {
    BIOS_INT_DIVIDE         = 0x00,
    BIOS_INT_TIMER_IRQ0     = 0x08,
    BIOS_INT_KBD_IRQ1       = 0x09,
    BIOS_INT_FLOPPY_IRQ6    = 0x0E,
    BIOS_INT_VIDEO          = 0x10,
    BIOS_INT_EQUIPMENT      = 0x11,
    BIOS_INT_MEMSIZE        = 0x12,
    BIOS_INT_DISK           = 0x13,
    BIOS_INT_SERIAL         = 0x14,
    BIOS_INT_SYSTEM         = 0x15,
    BIOS_INT_KEYBOARD       = 0x16,
    BIOS_INT_PRINTER        = 0x17,
    BIOS_INT_BASIC          = 0x18,
    BIOS_INT_BOOTSTRAP      = 0x19,
    BIOS_INT_TIME           = 0x1A,
    BIOS_INT_CTRL_BREAK     = 0x1B,
    BIOS_INT_USER_TICK      = 0x1C,
    BIOS_INT_VIDEO_PARMS    = 0x1D,
    BIOS_INT_DISKETTE_PARMS = 0x1E,
    BIOS_INT_VIDEO_FONT     = 0x1F,
    BIOS_INT_RTC_IRQ8       = 0x70,
    BIOS_INT_MOUSE_IRQ12    = 0x74,
    BIOS_INT_UNHANDLED      = 0xFF // catch-all stub: IRET
};

/* INT 15h E820h memory map. */
enum e820_type {
    E820_USABLE   = 1,
    E820_RESERVED = 2,
    E820_ACPI     = 3,
    E820_NVS      = 4
};

typedef struct e820_entry {
    u64 base;
    u64 length;
    u32 type;
} E820Entry;
#define BIOS_E820_MAX 8

typedef struct bios_disk {
    bool present;
    u8   drive_number;      // 00h/01h floppies, 80h+ hard disks
    bool is_floppy;
    u16  cylinders;
    u8   heads;
    u8   sectors_per_track;
    u16  bytes_per_sector;
    u8   cmos_type;         // floppy type nibble (4 = 1.44 MB)
} BIOSDisk;

typedef struct machine Machine;
typedef struct cpu CPU;

typedef struct bios {
    Machine *m;
    u8   rom[BIOS_ROM_SIZE];
    u32  entry_points[256];   // physical address of each vector's trap stub, 0 if none
    u32  trap_count;
    BIOSDisk disks[4];
    E820Entry e820[BIOS_E820_MAX];
    u8   e820_count;
    u32  base_mem_kb;         // 640
    u32  ext_mem_kb;          // above 1 MiB
    u8   boot_order[2];       // drive numbers to try
    struct {
        u8 mode, cols, rows, active_page;
        u8 cursor_start, cursor_end;
    } video;
    u64  tick_base_cycle;
    bool int13_extensions;    // report EDD support? GRUB falls back to CHS when false
    u32  services_handled;
    u32  services_unhandled;
} BIOS;

int bios_init(BIOS *bios, Machine *m);
void bios_build_rom(BIOS *bios);                 /* fill rom[] with IVT stubs, reset jump, signature */
void bios_post(BIOS *bios);                      /* IVT, BDA, CMOS, PIC/PIT defaults, then INT 19h */
bool bios_is_entry_point(const BIOS *bios, u32 phys_addr);
/* Dispatch a trapped service. Registers are read/written on the CPU; the caller then executes the stub's IRET. */
void bios_trap(BIOS *bios, u32 phys_addr);
void bios_set_disk(BIOS *bios, u8 index, const BIOSDisk *disk);

/* Service handlers. Each returns with the frame's CF set/cleared via bios_set_carry(). */
void bios_int10_video(BIOS *bios, CPU *cpu);
void bios_int11_equipment(BIOS *bios, CPU *cpu);
void bios_int12_memsize(BIOS *bios, CPU *cpu);
void bios_int13_disk(BIOS *bios, CPU *cpu);
void bios_int15_system(BIOS *bios, CPU *cpu);
void bios_int16_keyboard(BIOS *bios, CPU *cpu);
void bios_int19_bootstrap(BIOS *bios, CPU *cpu);
void bios_int1a_time(BIOS *bios, CPU *cpu);
void bios_irq0_timer(BIOS *bios, CPU *cpu);      /* BDA tick count, floppy motor timeout */
void bios_irq1_keyboard(BIOS *bios, CPU *cpu);   /* scan code → BDA keyboard buffer */
void bios_irq6_floppy(BIOS *bios, CPU *cpu);
void bios_unhandled(BIOS *bios, CPU *cpu, u8 vector);

/* Helpers operating on the trapped frame (FLAGS image at SS:SP+4 in real mode). */
void bios_set_carry(CPU *cpu, bool set);
void bios_set_zero(CPU *cpu, bool set);
u8 bios_bda_read8(BIOS *bios, u16 offset);
u16 bios_bda_read16(BIOS *bios, u16 offset);
void bios_bda_write8(BIOS *bios, u16 offset, u8 value);
void bios_bda_write16(BIOS *bios, u16 offset, u16 value);
void bios_bda_write32(BIOS *bios, u16 offset, u32 value);
void bios_teletype(BIOS *bios, u8 ch, u8 attr);
bool bios_kbd_buffer_push(BIOS *bios, u16 scancode_ascii);
bool bios_kbd_buffer_pop(BIOS *bios, u16 *out, bool peek);

#endif /* open386_BIOS_BIOS_H */
