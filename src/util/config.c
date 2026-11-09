/* open386 — configuration (stub, M0). Defaults follow ics-os/ics-os/Makefile `boot-floppy`. */
#include "util/config.h"

void config_set_defaults(struct config *cfg) { O386_STUB_TODO(M1); }
int  config_parse_args(struct config *cfg, int argc, char **argv) { O386_STUB_TODO(M1); return 0; }
void config_print_usage(const char *argv0) { O386_STUB_TODO(M1); }
int  config_validate(const struct config *cfg) { O386_STUB_TODO(M1); return 0; }
