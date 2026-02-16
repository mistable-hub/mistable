#ifndef SPLASH_H
#define SPLASH_H

#include <stdint.h>

#define SPLASH_WIDTH 320
#define SPLASH_HEIGHT 240

int splash_load(void);
const uint16_t *splash_pixels(void);

#endif
