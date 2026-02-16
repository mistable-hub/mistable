#include "sd_spi.h"

#include "board_pins.h"

void sd_spi_init(void) {
  (void)SD_SPI_INSTANCE;
  (void)PIN_SD_SCK;
  (void)PIN_SD_MOSI;
  (void)PIN_SD_MISO;
  (void)PIN_SD_CS;
}

bool sd_spi_card_present(void) {
  return true;
}
