#include "storage/sd_spi.h"

#include "board_pins.h"
#include "log.h"
#include "pico_compat.h"
#include "storage/ff_port.h"

#include "hardware/gpio.h"
#include "hardware/spi.h"

bool sd_spi_init_and_mount(void) {
  gpio_init(PIN_SD_SCK);
  gpio_init(PIN_SD_MOSI);
  gpio_init(PIN_SD_MISO);
  gpio_init(PIN_SD_CS);
  spi_init(SD_SPI_INSTANCE, 1000u * 1000u);

  ff_mount_t mount;
  if (!ff_port_mount(&mount)) {
    log_printf("[sd] mount failed on spi0 SCK=%d MOSI=%d MISO=%d CS=%d\n", PIN_SD_SCK, PIN_SD_MOSI, PIN_SD_MISO, PIN_SD_CS);
    return false;
  }

  log_printf("[sd] mount ok on spi0 SCK=%d MOSI=%d MISO=%d CS=%d\n", PIN_SD_SCK, PIN_SD_MOSI, PIN_SD_MISO, PIN_SD_CS);
  return true;
}
