#ifndef FF_PORT_H
#define FF_PORT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
  bool mounted;
} ff_mount_t;

typedef struct {
  void *opaque;
} ff_file_t;

bool ff_port_mount(ff_mount_t *mount);
bool ff_port_open(ff_mount_t *mount, ff_file_t *file, const char *path, size_t *size_out);
bool ff_port_read(ff_file_t *file, uint8_t *buf, size_t len, size_t *read_out);
void ff_port_close(ff_file_t *file);

#endif
