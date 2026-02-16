#include "sd_spi.h"
#include "board_pins.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

bool sd_spi_init(void) {
  gpio_init(PIN_SD_SCK);
  gpio_init(PIN_SD_MOSI);
  gpio_init(PIN_SD_MISO);
  gpio_init(PIN_SD_CS);
  gpio_set_dir(PIN_SD_CS, true);
  gpio_put(PIN_SD_CS, true);
  spi_init(SD_SPI_INSTANCE, 1000 * 1000);
  spi_set_format(SD_SPI_INSTANCE, 8, 0, 0, 0);
  return true;
}

bool sd_spi_mount(void) {
  return false;
}
