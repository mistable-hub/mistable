#ifndef LOG_H
#define LOG_H

#include <stddef.h>
#include <stdint.h>

void log_init(void);
void log_write(const char *msg);
void log_printf(const char *fmt, ...);
void log_flush(void);

#endif
