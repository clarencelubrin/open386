/* open386 — logging. One global sink; a message is emitted when its level is at or
 * below the configured maximum and its category bit is enabled. */
#include <stdarg.h>
#include "util/log.h"

/* Local state of log */
static struct {
    enum log_level max_level;   // current max level
    u32            categories;
    FILE          *sink;        // file pointer (can be file, STDOUT, STDERR, etc.)
} g_log = { LOG_INFO, LOGC_ALL, NULL };

/* Initialize the local g_log state */
void log_init(enum log_level max_level, u32 categories, FILE *sink) {
    g_log.max_level  = max_level;
    g_log.categories = categories;
    g_log.sink       = sink ? sink : stderr;    // default to STDERR
}
/* Set g_log level */
void log_set_level(enum log_level max_level) {
    g_log.max_level = max_level;
}
/* Set g_log categories */
void log_set_categories(u32 categories) {
    g_log.categories = categories;
}
/* Enable logging */
bool log_enabled(enum log_level level, u32 category) {
    return level <= g_log.max_level && (category & g_log.categories) != 0;
}
/* Log message to file descriptor with log_level level and category */
void log_msg(enum log_level level, u32 category, const char *fmt, ...) {
    FILE *out = g_log.sink ? g_log.sink : stderr;
    va_list ap;
    (void)category;
    fprintf(out, "[%s] ", log_level_name(level));
    va_start(ap, fmt);
    vfprintf(out, fmt, ap);
    va_end(ap);
    fputc('\n', out);
    fflush(out);
}
/* Convert level to log label string */
const char *log_level_name(enum log_level level) {
    switch (level) {
    case LOG_ERROR: return "error";
    case LOG_WARN:  return "warn";
    case LOG_INFO:  return "info";
    case LOG_DEBUG: return "debug";
    case LOG_TRACE: return "trace";
    case LOG_IO:    return "io";
    }
    return "?";
}
