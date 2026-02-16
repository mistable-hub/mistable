#ifndef LOG_H
#define LOG_H

#include <stddef.h>

void log_init(void);
void log_printf(const char *fmt, ...);
size_t log_pop(char *out, size_t out_size);

#endif
