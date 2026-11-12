/********************************************* Entry Point *********************************************
 * @file main.c
 * @author Lubrin, Clarence, U.
 * @details Entry point. Parses the configuration, builds the machine, runs it.
 *          Target command line (PLAN.md §1.3): open386 -fda ics-os/ics-os/ics-os-demo-floppy.img -m 64
 */
#include <stdio.h>
#include <stdlib.h>
#include "util/config.h"
#include "util/log.h"
#include "machine/machine.h"

int main(int argc, char **argv) {
    Config cfg;
    config_set_defaults(&cfg);
    if (config_parse_args(&cfg, argc, argv) != 0) {
        config_print_usage(argv[0]);
        return EXIT_FAILURE;
    }
    /* M0: machine_create/machine_run are declared in machine.h but not implemented yet. */
    O386_STUB_TODO(M1);
    fprintf(stderr, "open386: scaffolding only (M0); see PLAN.md\n");
    return EXIT_SUCCESS;
}
