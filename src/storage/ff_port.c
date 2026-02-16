#include "ff_port.h"

#include <stdio.h>

bool ff_port_mount(void) {
  FILE *f = fopen("assets/sdroot/VERSION.TXT", "rb");
  if (f == 0) {
    return false;
  }
  fclose(f);
  return true;
}

void ff_port_unmount(void) {
}
