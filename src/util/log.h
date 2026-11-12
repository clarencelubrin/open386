/********************************************* Logging *********************************************
 * @file log.h
 * @author Lubrin, Clarence, U.
 * @details Logging. Categories follow the source tree so a subsystem can be traced alone.
 */
#ifndef open386_UTIL_LOG_H
#define open386_UTIL_LOG_H

#include <stdio.h>
#include "types.h"

enum log_level {
    LOG_ERROR = 0,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG,
    LOG_TRACE,
    LOG_IO
};

enum log_category {
    LOGC_CPU     = 1u << 0,
    LOGC_DECODE  = 1u << 1,
    LOGC_MEM     = 1u << 2,
    LOGC_IO      = 1u << 3,
    LOGC_INT     = 1u << 4,
    LOGC_PAGING  = 1u << 5,
    LOGC_TASK    = 1u << 6,
    LOGC_FPU     = 1u << 7,
    LOGC_DEV     = 1u << 8,
    LOGC_BIOS    = 1u << 9,
    LOGC_MACHINE = 1u << 10,
    LOGC_DEBUG   = 1u << 11,
    LOGC_UI      = 1u << 12,
    LOGC_ALL     = 0x7FFFFFFF
};

void log_init(enum log_level max_level, u32 categories, FILE *sink);
void log_set_level(enum log_level max_level);
void log_set_categories(u32 categories);
bool log_enabled(enum log_level level, u32 category);
void log_msg(enum log_level level, u32 category, const char *fmt, ...);
const char *log_level_name(enum log_level level);

#define LOG(level, cat, ...)                                                                           \
    do {                                                                                               \
        if (log_enabled((level), (cat)))                                                               \
            log_msg((level), (cat), __VA_ARGS__);                                                      \
    } while (0)

#endif /* open386_UTIL_LOG_H */
