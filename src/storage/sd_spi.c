#include "sd_spi.h"

#include <stdio.h>

#include "ff_port.h"

int sd_spi_has_card(void) {
  FILE *fp = fopen("assets/sdroot/splash.raw", "rb");
  if (!fp) {
    return 0;
  }
  fclose(fp);
  return 1;
}

int sd_spi_mount(void) {
  if (!sd_spi_has_card()) {
    return -1;
  }
  return ff_port_mount();
}
