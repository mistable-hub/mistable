#ifndef HARDWARE_SPI_H
#define HARDWARE_SPI_H
#include <stdint.h>
typedef struct spi_inst { int unused; } spi_inst_t;
extern spi_inst_t spi0_inst;
#define spi0 (&spi0_inst)
static inline void spi_init(spi_inst_t *spi, uint32_t baud) {(void)spi;(void)baud;}
#endif
