/* open386 — configuration. Defaults follow ics-os/ics-os/Makefile `boot-floppy`
 * (`qemu-system-i386 -fda … -boot a -m 64M`); option spelling follows QEMU where
 * PLAN.md already uses it (-fda, -m, -cpu, -bios, -s, -S). */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/config.h"
#include "util/log.h"
#include "debugger/trace.h"

/* Load default config */
void config_set_defaults(struct config *cfg) {
    memset(cfg, 0, sizeof *cfg);
    cfg->ram_mb           = 64;
    cfg->cpu_model        = "i386-icsos";
    cfg->core_mhz         = 33;
    cfg->display          = DISPLAY_TERM;
    cfg->boot_from_floppy = true;
}

/* Parses a decimal/hex unsigned integer; an optional trailing "M" or "m" is ignored
 * so "-m 64M" works as in QEMU. Returns false on garbage or overflow. */
static bool parse_u64(const char *s, u64 *out) {
    char *end;
    unsigned long long v;
    if (!s || !*s) return false;
    errno = 0;
    v = strtoull(s, &end, 0);
    if (errno || end == s) return false;
    if ((*end == 'M' || *end == 'm') && end[1] == '\0') end++;
    if (*end) return false;
    *out = v;
    return true;
}

static int parse_trace_mask(const char *list, u32 *mask) {
    static const struct { const char *name; u32 bit; } names[] = {
        { "cpu",  TRACE_CPU  }, { "regs", TRACE_REGS }, { "int",  TRACE_INT  },
        { "io",   TRACE_IO   }, { "pf",   TRACE_PF   }, { "task", TRACE_TASK },
        { "bios", TRACE_BIOS }, { "dev",  TRACE_DEV  }, { "mode", TRACE_MODE },
    };
    const char *p = list;
    while (*p) {
        const char *q = strchr(p, ',');
        size_t n = q ? (size_t)(q - p) : strlen(p);
        size_t i;
        if (n == 3 && !strncmp(p, "all", 3)) {
            *mask = ~0u;
        } else {
            for (i = 0; i < sizeof names / sizeof names[0]; i++)
                if (strlen(names[i].name) == n && !strncmp(p, names[i].name, n)) {
                    *mask |= names[i].bit;
                    break;
                }
            if (i == sizeof names / sizeof names[0]) {
                fprintf(stderr, "open386: unknown trace category '%.*s'\n", (int)n, p);
                return -1;
            }
        }
        if (!q) break;
        p = q + 1;
    }
    return 0;
}

static int parse_log_level(const char *s, enum log_level *lvl) {
    static const char *names[] = { "error", "warn", "info", "debug", "trace" };
    for (size_t i = 0; i < sizeof names / sizeof names[0]; i++)
        if (!strcmp(s, names[i])) {
            *lvl = (enum log_level)i;
            return 0;
        }
    fprintf(stderr, "open386: unknown log level '%s'\n", s);
    return -1;
}

/* Parse the arguments into config cfg */
int config_parse_args(struct config *cfg, int argc, char **argv) {
    enum log_level log_lvl = LOG_INFO;  // Initialize log level
    bool log_lvl_set = false;

    for (int i = 1; i < argc; i++) {
        const char *a = argv[i];
/* Options taking a value: fetch it (or fail) up front. */
#define NEED_ARG()                                                              \
        do {                                                                    \
            if (i + 1 >= argc) {                                                \
                fprintf(stderr, "open386: option '%s' needs an argument\n", a); \
                return -1;                                                      \
            }                                                                   \
            i++;                                                                \
        } while (0)
        u64 n;

        if (!strcmp(a, "-h") || !strcmp(a, "-help") || !strcmp(a, "--help")) {
            config_print_usage(argv[0]);    // Print open836 usage
            exit(EXIT_SUCCESS);
        } else if (!strcmp(a, "-fda")) {    // Set floppy file for a
            NEED_ARG();                     // Return an error if there is no arguments passed in the flag
            cfg->floppy_a_path = argv[i];
        } else if (!strcmp(a, "-fdb")) {    // Set floppy file for b
            NEED_ARG(); 
            cfg->floppy_b_path = argv[i];
        } else if (!strcmp(a, "-hda")) {    // Set hard drive path
            NEED_ARG(); 
            cfg->hd_path = argv[i];
        } else if (!strcmp(a, "-bios")) {   // Set bios rom path
            NEED_ARG(); 
            cfg->bios_rom_path = argv[i];
        } else if (!strcmp(a, "-m")) {      // Set memory size
            NEED_ARG();
            // Validate the size of the passed memory size for the open836 emulator
            if (!parse_u64(argv[i], &n) || n == 0 || n > 4096) {
                fprintf(stderr, "open386: bad memory size '%s' (1..4096 MiB)\n", argv[i]);
                return -1;
            }
            cfg->ram_mb = (u32)n;
        } else if (!strcmp(a, "-cpu")) {
            // "-cpu i386dx,+cpuid,-fpu"
            // model name up to the first comma, rest = overrides.
            char *comma;
            NEED_ARG();
            comma = strchr(argv[i], ',');
            if (comma) {
                *comma = '\0';
                cfg->cpu_overrides = comma + 1;
            }
            if (*argv[i]) cfg->cpu_model = argv[i];
        } else if (!strcmp(a, "-mhz")) {    // Set the cpu clock speed
            NEED_ARG();
            // Validate the cpu clock speed
            if (!parse_u64(argv[i], &n) || n == 0 || n > 10000) {
                fprintf(stderr, "open386: bad core clock '%s'\n", argv[i]);
                return -1;
            }
            cfg->core_mhz = (u32)n;
        } else if (!strcmp(a, "-display")) {
            // Set the display setting for the open836
            NEED_ARG();
            if (!strcmp(argv[i], "none"))      cfg->display = DISPLAY_NONE;     // Run in headless
            else if (!strcmp(argv[i], "term")) cfg->display = DISPLAY_TERM;     
            else if (!strcmp(argv[i], "sdl"))  cfg->display = DISPLAY_SDL;      // Run using SDL library
            else {
                fprintf(stderr, "open386: unknown display '%s' (none|term|sdl)\n", argv[i]);
                return -1;
            }
        } else if (!strcmp(a, "-nographic")) {      // Set the display to headless mode
            cfg->display = DISPLAY_NONE;
        } else if (!strcmp(a, "-s")) {              // Set the gdb port
            if (!cfg->gdb_port) cfg->gdb_port = 1234;
        } else if (!strcmp(a, "-S")) {              // Set the start_stopped flag
            cfg->start_stopped = true;
        } else if (!strcmp(a, "-gdb")) {            // Set the gdb debugger
            NEED_ARG();
            if (!parse_u64(argv[i], &n) || n == 0 || n > 65535) {
                fprintf(stderr, "open386: bad gdb port '%s'\n", argv[i]);
                return -1;
            }
            cfg->gdb_port = (u16)n;
        } else if (!strcmp(a, "-trace")) {          // Trace the open836 execution
            NEED_ARG();
            if (parse_trace_mask(argv[i], &cfg->trace_mask) != 0) return -1;
        } else if (!strcmp(a, "-trace-file")) {     // Output trace to a file
            NEED_ARG(); cfg->trace_path = argv[i];
        } else if (!strcmp(a, "-max-insn")) {       // Set maximum instruction count
            NEED_ARG();
            if (!parse_u64(argv[i], &n)) {
                fprintf(stderr, "open386: bad instruction count '%s'\n", argv[i]);
                return -1;
            }
            cfg->max_instructions = n;
        } else if (!strcmp(a, "-vga-dump")) {       // Dump vga output to a file
            NEED_ARG(); cfg->vga_dump_path = argv[i];
        } else if (!strcmp(a, "-boot")) {           // Set boot floppy 
            NEED_ARG();
            if (!strcmp(argv[i], "a"))      cfg->boot_from_floppy = true;
            else if (!strcmp(argv[i], "c")) cfg->boot_from_floppy = false;
            else {
                fprintf(stderr, "open386: bad boot order '%s' (a|c)\n", argv[i]);
                return -1;
            }
        } else if (!strcmp(a, "-log")) {            // Enable/disable logging
            NEED_ARG();
            if (parse_log_level(argv[i], &log_lvl) != 0) return -1;
            log_lvl_set = true;
        } else {
            fprintf(stderr, "open386: unknown option '%s'\n", a);
            return -1;
        }
#undef NEED_ARG
    }

    log_init(log_lvl_set ? log_lvl : LOG_INFO, LOGC_ALL, stderr);
    return config_validate(cfg);
}

/* Print usage documentation for open386 */
void config_print_usage(const char *argv0) {
    fprintf(stderr,
        "usage: %s [options]\n"
        "  -fda FILE         floppy A image (1.44 MB)         -fdb FILE   floppy B image\n"
        "  -hda FILE         IDE disk image (M7+)\n"
        "  -bios FILE        real BIOS ROM instead of the built-in HLE BIOS (M6+)\n"
        "  -m MB             RAM in MiB (default 64; '64M' accepted)\n"
        "  -cpu MODEL[,+f,-f]  i386dx | i386-icsos (default) | i486dx | pentium, with feature overrides\n"
        "  -mhz N            virtual core clock in MHz (default 33)\n"
        "  -display KIND     none | term (default) | sdl      -nographic  same as -display none\n"
        "  -boot a|c         boot order: floppy first (default) or disk first\n"
        "  -s                GDB stub on port 1234            -gdb PORT   GDB stub on PORT\n"
        "  -S                start stopped; wait for the debugger\n"
        "  -trace LIST       cpu,regs,int,io,pf,task,bios,dev,mode,all   -trace-file FILE\n"
        "  -max-insn N       stop after N instructions (tests)\n"
        "  -vga-dump FILE    headless: write the VGA text buffer here on exit\n"
        "  -log LEVEL        error | warn | info (default) | debug | trace\n"
        "  -h                this help\n",
        argv0);
}

/* Validation of configuration set by the user */
int config_validate(const struct config *cfg) {
    if (cfg->ram_mb == 0 || cfg->ram_mb > 4096) {   // Validate ram size, must be 1-4096 MiB
        fprintf(stderr, "open386: RAM must be 1..4096 MiB\n");
        return -1;
    }
    if (cfg->core_mhz == 0) {                       // Clock MHz must be non-zero
        fprintf(stderr, "open386: core clock must be non-zero\n");
        return -1;
    }
    if (!cfg->floppy_a_path && !cfg->hd_path && !cfg->bios_rom_path) {  // Invalid image file for boot
        fprintf(stderr, "open386: nothing to boot; give -fda IMAGE (or -hda / -bios)\n");
        return -1;
    }
    if (cfg->boot_from_floppy && !cfg->floppy_a_path && cfg->hd_path) { // No -fda found for -boot a
        fprintf(stderr, "open386: -boot a but no -fda; use -boot c\n");
        return -1;
    }
    if (cfg->start_stopped && !cfg->gdb_port) {                         // No gdb port detected for debugger
        fprintf(stderr, "open386: -S needs a debugger (-s or -gdb PORT)\n");
        return -1;
    }
    return 0;
}
