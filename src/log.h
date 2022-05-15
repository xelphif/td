#pragma once

enum log_class {
    LOG_CLASS_NONE,
    LOG_CLASS_ERR,
    LOG_CLASS_WARN,
    LOG_CLASS_INFO
};

void log_init(enum log_class log_level);
void log_msg(enum log_class log_class, const char *file, int lineno,
             const char *fmt, ...);

#define LOG_ERR(...) log_msg(LOG_CLASS_ERR, __FILE__, __LINE__, __VA_ARGS__);
#define LOG_WARN(...) log_msg(LOG_CLASS_WARN, __FILE__, __LINE__, __VA_ARGS__);
#define LOG_INFO(...) log_msg(LOG_CLASS_INFO, __FILE__, __LINE__, __VA_ARGS__);

#define INVALID_ARG "Invalid argument."
#define NOT_ENOUGH_ARGS "Not enough arguments."
