#include "splash.h"

#include <stdio.h>

#include "log.h"

#define SPLASH_SIZE_BYTES 153600

static unsigned char g_splash[SPLASH_SIZE_BYTES];

bool splash_load_from_sd(void) {
  FILE *f = fopen("assets/sdroot/splash.raw", "rb");
  size_t total = 0;
  size_t chunk;
  if (f == 0) {
    log_write("storage: /splash.raw open fail\n");
    return false;
  }
  while (total < SPLASH_SIZE_BYTES) {
    size_t remain = SPLASH_SIZE_BYTES - total;
    size_t want = remain >= 4096 ? 4096 : remain;
    chunk = fread(g_splash + total, 1, want, f);
    if (chunk == 0) {
      fclose(f);
      log_write("storage: /splash.raw short read\n");
      return false;
    }
    total += chunk;
  }
  if (fgetc(f) != EOF) {
    fclose(f);
    log_write("storage: /splash.raw wrong size\n");
    return false;
  }
  fclose(f);
  log_write("storage: /splash.raw loaded\n");
  return true;
}
