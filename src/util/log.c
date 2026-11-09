/* open386 — logging (stub, M0). */
#include <stdarg.h>
#include "util/log.h"

void log_init(enum log_level max_level, u32 categories, FILE *sink) { O386_STUB_TODO(M1); }
void log_set_level(enum log_level max_level) { O386_STUB_TODO(M1); }
void log_set_categories(u32 categories) { O386_STUB_TODO(M1); }
bool log_enabled(enum log_level level, u32 category) { O386_STUB_TODO(M1); return false; }
void log_msg(enum log_level level, u32 category, const char *fmt, ...) { O386_STUB_TODO(M1); }
const char *log_level_name(enum log_level level) { O386_STUB_TODO(M1); return ""; }
