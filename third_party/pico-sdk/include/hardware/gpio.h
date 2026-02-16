#ifndef HARDWARE_GPIO_H
#define HARDWARE_GPIO_H
#include <stdbool.h>
#include <stdint.h>
static inline void gpio_init(uint pin) {(void)pin;}
static inline void gpio_set_dir(uint pin, bool out) {(void)pin;(void)out;}
static inline void gpio_put(uint pin, bool value) {(void)pin;(void)value;}
#endif
