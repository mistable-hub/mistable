#ifndef LOG_H
#define LOG_H

#include <stdbool.h>
#include <stddef.h>

void log_init(void);
void log_printf(const char *fmt, ...);
size_t log_read_chunk(char *dst, size_t max_len);
bool log_has_data(void);

#endif
