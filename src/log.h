#ifndef LOG_H
#define LOG_H

#include <stdbool.h>
#include <stddef.h>

void log_init(void);
void log_write(const char *msg);
bool log_pop(char *out, size_t out_len);

#endif
