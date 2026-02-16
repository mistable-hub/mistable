#ifndef SPLASH_H
#define SPLASH_H

#include <stdbool.h>
#include <stdint.h>

#define SPLASH_PIXELS (320u * 240u)
#define SPLASH_RAW_SIZE_BYTES (SPLASH_PIXELS * 2u)

bool splash_try_load(void);
const uint16_t *splash_pixels(void);

#endif
