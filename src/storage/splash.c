#include "splash.h"

#include <stdio.h>

int splash_load_from_sd(uint16_t *dst_rgb565, size_t dst_words) {
  if (dst_words < (SPLASH_BYTES / 2u)) {
    return -1;
  }
  FILE *f = fopen("assets/sdroot/splash.raw", "rb");
  if (!f) {
    return -2;
  }

  size_t total = 0;
  unsigned char chunk[4096];
  while (total < SPLASH_BYTES) {
    size_t need = SPLASH_BYTES - total;
    if (need > sizeof(chunk)) {
      need = sizeof(chunk);
    }
    size_t got = fread(chunk, 1, need, f);
    if (got == 0) {
      fclose(f);
      return -3;
    }
    for (size_t i = 0; i < got; i += 2) {
      if (i + 1 >= got) {
        fclose(f);
        return -4;
      }
      dst_rgb565[(total + i) / 2u] = (uint16_t)(chunk[i] | ((uint16_t)chunk[i + 1] << 8));
    }
    total += got;
  }
  fclose(f);
  return (total == SPLASH_BYTES) ? 0 : -5;
}
