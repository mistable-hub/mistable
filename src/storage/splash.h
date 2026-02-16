#ifndef SPLASH_H
#define SPLASH_H

#include <stdbool.h>
#include <stdint.h>

bool splash_load_from_fs(void);
const uint16_t *splash_get_pixels(void);
bool splash_is_loaded(void);

#endif
