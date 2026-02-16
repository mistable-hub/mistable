#ifndef SD_SPI_H
#define SD_SPI_H

#include <stdbool.h>

void sd_spi_init(void);
bool sd_spi_card_present(void);

#endif
