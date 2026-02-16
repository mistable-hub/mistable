#include "sd_spi.h"

bool sd_spi_init(void) {
  return false;
}

bool sd_spi_read_blocks(uint32_t lba, uint8_t *dst, size_t block_count) {
  (void)lba;
  (void)dst;
  (void)block_count;
  return false;
}
