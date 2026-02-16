#ifndef BOARD_PINS_H
#define BOARD_PINS_H

#include "hardware/spi.h"

#define PIN_DVI_D2_P    32
#define PIN_DVI_D2_N    33
#define PIN_DVI_D1_P    34
#define PIN_DVI_D1_N    35
#define PIN_DVI_D0_P    36
#define PIN_DVI_D0_N    37
#define PIN_DVI_CLK_P   39
#define PIN_DVI_CLK_N   38

#define PIN_DVI_SDA     44
#define PIN_DVI_SCL     46
#define PIN_DVI_CEC      6

#define SD_SPI_INSTANCE spi0
#define PIN_SD_SCK      30
#define PIN_SD_MOSI     31
#define PIN_SD_MISO     40
#define PIN_SD_CS       43

#define PIN_PIO_USB_DP  46
#define PIN_PIO_USB_DM  47

#if PIN_DVI_D2_P != 32
#error "PIN_DVI_D2_P must be 32"
#endif
#if PIN_DVI_D2_N != 33
#error "PIN_DVI_D2_N must be 33"
#endif
#if PIN_DVI_D1_P != 34
#error "PIN_DVI_D1_P must be 34"
#endif
#if PIN_DVI_D1_N != 35
#error "PIN_DVI_D1_N must be 35"
#endif
#if PIN_DVI_D0_P != 36
#error "PIN_DVI_D0_P must be 36"
#endif
#if PIN_DVI_D0_N != 37
#error "PIN_DVI_D0_N must be 37"
#endif
#if PIN_DVI_CLK_P != 39
#error "PIN_DVI_CLK_P must be 39"
#endif
#if PIN_DVI_CLK_N != 38
#error "PIN_DVI_CLK_N must be 38"
#endif
#if PIN_DVI_SDA != 44
#error "PIN_DVI_SDA must be 44"
#endif
#if PIN_DVI_SCL != 46
#error "PIN_DVI_SCL must be 46"
#endif
#if PIN_DVI_CEC != 6
#error "PIN_DVI_CEC must be 6"
#endif
#if PIN_SD_SCK != 30
#error "PIN_SD_SCK must be 30"
#endif
#if PIN_SD_MOSI != 31
#error "PIN_SD_MOSI must be 31"
#endif
#if PIN_SD_MISO != 40
#error "PIN_SD_MISO must be 40"
#endif
#if PIN_SD_CS != 43
#error "PIN_SD_CS must be 43"
#endif
#if PIN_PIO_USB_DP != 46
#error "PIN_PIO_USB_DP must be 46"
#endif
#if PIN_PIO_USB_DM != 47
#error "PIN_PIO_USB_DM must be 47"
#endif

_Static_assert(SD_SPI_INSTANCE == spi0, "SD_SPI_INSTANCE must be spi0");

#endif
