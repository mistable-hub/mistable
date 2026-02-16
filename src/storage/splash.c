#include "splash.h"

#include <stdio.h>
#include <string.h>

#include "ff.h"

static uint16_t g_splash[SPLASH_WIDTH * SPLASH_HEIGHT];

int splash_load(void) {
  FIL file;
  if (f_open(&file, "assets/sdroot/splash.raw", FA_READ) != FR_OK) {
    return -1;
  }

  unsigned char chunk[4096];
  size_t total = 0;
  while (total < sizeof(g_splash)) {
    UINT got = 0;
    UINT want = (UINT)sizeof(chunk);
    if (want > (UINT)(sizeof(g_splash) - total)) {
      want = (UINT)(sizeof(g_splash) - total);
    }
    if (f_read(&file, chunk, want, &got) != FR_OK) {
      f_close(&file);
      return -2;
    }
    if (got == 0) {
      break;
    }
    memcpy(((unsigned char *)g_splash) + total, chunk, got);
    total += got;
  }

  f_close(&file);
  if (total != sizeof(g_splash)) {
    return -3;
  }
  return 0;
}

const uint16_t *splash_pixels(void) {
  return g_splash;
}
