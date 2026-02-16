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
#error "PIN_DVI_D2_P mismatch"
#endif
#if PIN_DVI_D2_N != 33
#error "PIN_DVI_D2_N mismatch"
#endif
#if PIN_DVI_D1_P != 34
#error "PIN_DVI_D1_P mismatch"
#endif
#if PIN_DVI_D1_N != 35
#error "PIN_DVI_D1_N mismatch"
#endif
#if PIN_DVI_D0_P != 36
#error "PIN_DVI_D0_P mismatch"
#endif
#if PIN_DVI_D0_N != 37
#error "PIN_DVI_D0_N mismatch"
#endif
#if PIN_DVI_CLK_P != 39
#error "PIN_DVI_CLK_P mismatch"
#endif
#if PIN_DVI_CLK_N != 38
#error "PIN_DVI_CLK_N mismatch"
#endif
#if PIN_DVI_SDA != 44
#error "PIN_DVI_SDA mismatch"
#endif
#if PIN_DVI_SCL != 46
#error "PIN_DVI_SCL mismatch"
#endif
#if PIN_DVI_CEC != 6
#error "PIN_DVI_CEC mismatch"
#endif
#if PIN_SD_SCK != 30
#error "PIN_SD_SCK mismatch"
#endif
#if PIN_SD_MOSI != 31
#error "PIN_SD_MOSI mismatch"
#endif
#if PIN_SD_MISO != 40
#error "PIN_SD_MISO mismatch"
#endif
#if PIN_SD_CS != 43
#error "PIN_SD_CS mismatch"
#endif
#if PIN_PIO_USB_DP != 46
#error "PIN_PIO_USB_DP mismatch"
#endif
#if PIN_PIO_USB_DM != 47
#error "PIN_PIO_USB_DM mismatch"
#endif

#endif
