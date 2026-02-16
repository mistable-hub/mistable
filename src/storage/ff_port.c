#include "ff_port.h"

#include <stdio.h>

int ff_port_mount(void) {
  FILE *f = fopen("assets/sdroot/splash.raw", "rb");
  if (!f) {
    return -1;
  }
  fclose(f);
  return 0;
}
