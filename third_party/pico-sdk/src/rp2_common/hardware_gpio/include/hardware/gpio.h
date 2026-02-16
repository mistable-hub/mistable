#ifndef HARDWARE_GPIO_H
#define HARDWARE_GPIO_H

#include <stdbool.h>
#include <stdint.h>

enum gpio_function {
  GPIO_FUNC_NULL = 0,
  GPIO_FUNC_SIO = 1,
  GPIO_FUNC_SPI = 2,
  GPIO_FUNC_UART = 3,
  GPIO_FUNC_I2C = 4,
  GPIO_FUNC_PWM = 5,
  GPIO_FUNC_PIO0 = 6,
  GPIO_FUNC_PIO1 = 7,
};

void gpio_init(uint32_t gpio);
void gpio_set_dir(uint32_t gpio, bool out);
void gpio_put(uint32_t gpio, bool value);
void gpio_set_function(uint32_t gpio, enum gpio_function fn);

#endif
