#ifndef SD_SPI_H
#define SD_SPI_H

#include <stddef.h>
#include <stdint.h>

int sd_spi_init(void);
int sd_spi_read_blocks(uint32_t lba, uint8_t *dst, size_t count_512b);

#endif
