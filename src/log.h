#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

void log_init(void);
void log_printf(const char *fmt, ...);
size_t log_drain(char *out, size_t out_len);
bool log_has_data(void);

#endif
