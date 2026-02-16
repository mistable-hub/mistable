#include "splash.h"
#include "ff.h"
#include "log.h"

#define SPLASH_WIDTH 320
#define SPLASH_HEIGHT 240

static uint16_t s_splash[SPLASH_WIDTH * SPLASH_HEIGHT];
static bool s_loaded = false;

bool splash_load_from_fs(void) {
  FIL f;
  UINT br = 0;
  FRESULT res = f_open(&f, "/splash.raw", FA_READ);
  if (res != FR_OK) {
    log_write("splash: open failed\n");
    s_loaded = false;
    return false;
  }
  res = f_read(&f, s_splash, sizeof(s_splash), &br);
  f_close(&f);
  if (res != FR_OK || br != sizeof(s_splash)) {
    log_write("splash: read failed\n");
    s_loaded = false;
    return false;
  }
  s_loaded = true;
  return true;
}

const uint16_t *splash_get_pixels(void) {
  return s_splash;
}

bool splash_is_loaded(void) {
  return s_loaded;
}
