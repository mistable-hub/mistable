#include "sd_spi.h"

#include "board_pins.h"

int sd_spi_init(void) {
  (void)PIN_SD_SCK;
  (void)PIN_SD_MOSI;
  (void)PIN_SD_MISO;
  (void)PIN_SD_CS;
  return 0;
}

int sd_spi_read_blocks(uint32_t lba, uint8_t *dst, size_t count_512b) {
  (void)lba;
  (void)dst;
  (void)count_512b;
  return -1;
}
