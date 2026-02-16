#ifndef PICO_STDLIB_H
#define PICO_STDLIB_H
#include <stdint.h>
#include <stdbool.h>
static inline void stdio_init_all(void) {}
static inline void sleep_ms(uint32_t ms) {(void)ms;}
static inline uint32_t to_ms_since_boot(uint64_t t) { return (uint32_t)t; }
static inline uint64_t get_absolute_time(void) { static uint64_t t; t += 1000; return t; }
#endif
