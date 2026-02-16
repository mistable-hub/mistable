#ifndef PICO_TIME_H
#define PICO_TIME_H

#include <stdint.h>

typedef struct absolute_time {
  uint64_t _private_us_since_boot;
} absolute_time_t;

absolute_time_t get_absolute_time(void);
uint64_t time_us_64(void);

#endif
