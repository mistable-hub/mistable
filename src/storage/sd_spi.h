#ifndef SD_SPI_H
#define SD_SPI_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool sd_spi_init(void);
bool sd_spi_read_blocks(uint32_t lba, uint8_t *dst, size_t block_count);

#endif
