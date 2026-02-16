#include "ff_port.h"

#include <stdbool.h>

bool ff_port_mount(void) {
  return false;
}

bool ff_port_read_file(const char *path, void *dst, unsigned *size_inout) {
  (void)path;
  (void)dst;
  (void)size_inout;
  return false;
}
