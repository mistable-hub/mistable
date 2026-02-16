#ifndef LOG_H
#define LOG_H

#include <stdbool.h>
#include <stddef.h>

void log_init(void);
void log_write(const char *msg);
void log_printf(const char *fmt, ...);
bool log_try_pop_line(char *out, size_t out_size);

#endif
