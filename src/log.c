#include "log.h"

#include <stdio.h>
#include <stdarg.h>

static enum log_class log_level = LOG_CLASS_INFO;

#define CLR_RED_HL "\033[41m"
#define CLR_YELLOW_HL "\033[43m"
#define CLR_BLUE "\033[0;34m"
#define CLR_RESET "\033[0m"

static const struct {
    const char *name;
    const char *log_prefix;
    const char *color;
} log_level_map[] = {
    [LOG_CLASS_NONE] = {"none",     "NONE", ""           },
    [LOG_CLASS_ERR]  = { "error",   "ERR",  CLR_RED_HL   },
    [LOG_CLASS_WARN] = { "warning", "WARN", CLR_YELLOW_HL},
    [LOG_CLASS_INFO] = { "info",    "INFO", CLR_BLUE     },
};

void log_init(enum log_class _log_level)
{
    log_level = _log_level;
}

void log_msg(enum log_class log_class, const char *file, int lineno,
             const char *fmt, ...)
{
    if (log_class > log_level)
        return;

    const char *prefix = log_level_map[log_class].log_prefix;
    const char *color  = log_level_map[log_class].color;

    fprintf(stderr, "[%s%s%s] %s:%d: ", color, prefix, CLR_RESET, file, lineno);

    va_list va;
    va_start(va, fmt);
    vfprintf(stderr, fmt, va);
    va_end(va);

    fputc('\n', stderr);
}
