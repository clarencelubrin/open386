/********************************************* Configuration *********************************************
 * @file config.h
 * @author Lubrin, Clarence, U.
 * @details Command-line / run configuration.
 */
#ifndef open386_UTIL_CONFIG_H
#define open386_UTIL_CONFIG_H

#include "types.h"

enum display_kind {
    DISPLAY_NONE = 0, // headless; VGA text buffer can still be dumped
    DISPLAY_TERM,     // curses text console
    DISPLAY_SDL       // SDL2 window, text + graphics modes (optional build)
};

typedef struct config {
    const char *floppy_a_path;
    const char *floppy_b_path;
    const char *hd_path;             // optional IDE image (M7+)
    const char *bios_rom_path;       // NULL = built-in HLE BIOS (PLAN.md §6.3)
    u32         ram_mb;              // default 64
    const char *cpu_model;           // "i386dx", "i386-icsos" (default), "i486dx", "pentium"
    const char *cpu_overrides;       // e.g. "+cpuid,-fpu" (PLAN.md §4.3)
    u32         core_mhz;            // virtual core clock used to pace devices, default 33
    enum display_kind display;
    bool        start_stopped;       // wait for the debugger before the first instruction
    u16         gdb_port;            // 0 = disabled
    u32         trace_mask;          // enum trace_flags bits
    const char *trace_path;
    u64         max_instructions;    // 0 = unlimited; used by tests
    const char *vga_dump_path;       // headless: dump VGA text buffer here on exit
    bool        boot_from_floppy;    // INT 19h order: true = A: first (QEMU `-boot a`)
} Config;

void config_set_defaults(Config *cfg);
int config_parse_args(Config *cfg, int argc, char **argv);
void config_print_usage(const char *argv0);
int config_validate(const Config *cfg);

#endif /* open386_UTIL_CONFIG_H */
