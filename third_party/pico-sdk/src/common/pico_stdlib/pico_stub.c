#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

void stdio_init_all(void) {
}

void sleep_ms(uint32_t ms) {
  (void)ms;
}

absolute_time_t get_absolute_time(void) {
  absolute_time_t t;
  t._private_us_since_boot = 0;
  return t;
}

uint64_t time_us_64(void) {
  struct timespec ts;
  if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0) {
    return (uint64_t)ts.tv_sec * 1000000ULL + (uint64_t)(ts.tv_nsec / 1000ULL);
  }
  return 0;
}

void gpio_init(uint32_t gpio) {
  (void)gpio;
}

void gpio_set_dir(uint32_t gpio, bool out) {
  (void)gpio;
  (void)out;
}

void gpio_put(uint32_t gpio, bool value) {
  (void)gpio;
  (void)value;
}

void gpio_set_function(uint32_t gpio, enum gpio_function fn) {
  (void)gpio;
  (void)fn;
}

void spi_init(spi_inst_t *spi, uint32_t baudrate) {
  (void)spi;
  (void)baudrate;
}

int spi_write_blocking(spi_inst_t *spi, const uint8_t *src, size_t len) {
  (void)spi;
  (void)src;
  return (int)len;
}

int spi_read_blocking(spi_inst_t *spi, uint8_t repeated_tx_data, uint8_t *dst, size_t len) {
  (void)spi;
  (void)repeated_tx_data;
  if (dst && len) {
    for (size_t i = 0; i < len; ++i) {
      dst[i] = 0;
    }
  }
  return (int)len;
}

void spi_set_format(spi_inst_t *spi, uint bits, uint cpol, uint cpha, uint order) {
  (void)spi;
  (void)bits;
  (void)cpol;
  (void)cpha;
  (void)order;
}
