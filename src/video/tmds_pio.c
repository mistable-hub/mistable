#include "video/tmds_pio.h"
#include "board_pins.h"
#include "pico_compat.h"

#include "hardware/gpio.h"

void tmds_pio_init(void) {
  gpio_init(PIN_DVI_D2_P);
  gpio_init(PIN_DVI_D2_N);
  gpio_init(PIN_DVI_D1_P);
  gpio_init(PIN_DVI_D1_N);
  gpio_init(PIN_DVI_D0_P);
  gpio_init(PIN_DVI_D0_N);
  gpio_init(PIN_DVI_CLK_P);
  gpio_init(PIN_DVI_CLK_N);
}

void tmds_pio_start(void) {
}
