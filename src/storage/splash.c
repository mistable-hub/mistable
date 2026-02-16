#include "storage/splash.h"

#include <stddef.h>
#include <stdint.h>

#include "log.h"
#include "storage/ff_port.h"

static uint16_t g_splash[SPLASH_PIXELS];

const uint16_t *splash_pixels(void) {
  return g_splash;
}

bool splash_try_load(void) {
  ff_mount_t mount;
  ff_file_t file;
  size_t size = 0;

  if (!ff_port_mount(&mount)) {
    log_write("[splash] mount fail\n");
    return false;
  }

  if (!ff_port_open(&mount, &file, "assets/sdroot/splash.raw", &size)) {
    log_write("[splash] /splash.raw missing\n");
    return false;
  }

  if (size != SPLASH_RAW_SIZE_BYTES) {
    log_printf("[splash] invalid size=%lu expected=%lu\n", (unsigned long)size, (unsigned long)SPLASH_RAW_SIZE_BYTES);
    ff_port_close(&file);
    return false;
  }

  uint8_t chunk[4096];
  size_t total = 0;
  while (total < size) {
    size_t rd = 0;
    const size_t want = (size - total) > sizeof(chunk) ? sizeof(chunk) : (size - total);
    if (!ff_port_read(&file, chunk, want, &rd) || rd == 0u) {
      ff_port_close(&file);
      log_write("[splash] read fail\n");
      return false;
    }
    for (size_t i = 0; i + 1u < rd; i += 2u) {
      const size_t pix = (total + i) / 2u;
      g_splash[pix] = (uint16_t)(chunk[i] | ((uint16_t)chunk[i + 1u] << 8u));
    }
    total += rd;
  }
  ff_port_close(&file);
  log_write("[splash] splash.raw loaded (320x240 RGB565)\n");
  return true;
}
