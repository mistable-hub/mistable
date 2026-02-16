#ifndef SPLASH_H
#define SPLASH_H

#include <stddef.h>
#include <stdint.h>

#define SPLASH_WIDTH 320
#define SPLASH_HEIGHT 240
#define SPLASH_BYTES (SPLASH_WIDTH * SPLASH_HEIGHT * 2)

int splash_load_from_sd(uint16_t *dst_rgb565, size_t dst_words);

#endif
