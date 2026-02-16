#ifndef HARDWARE_SPI_H
#define HARDWARE_SPI_H

#include <stddef.h>
#include <stdint.h>

typedef struct spi_inst {
  uint8_t dummy;
} spi_inst_t;

typedef unsigned int uint;

extern spi_inst_t *spi0;

void spi_init(spi_inst_t *spi, uint32_t baudrate);
int spi_write_blocking(spi_inst_t *spi, const uint8_t *src, size_t len);
int spi_read_blocking(spi_inst_t *spi, uint8_t repeated_tx_data, uint8_t *dst, size_t len);
void spi_set_format(spi_inst_t *spi, uint bits, uint cpol, uint cpha, uint order);

#endif
