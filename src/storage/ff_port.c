#include "storage/ff_port.h"

#include <stdio.h>

bool ff_port_mount(ff_mount_t *mount) {
  if (mount == 0) {
    return false;
  }
  mount->mounted = true;
  return true;
}

bool ff_port_open(ff_mount_t *mount, ff_file_t *file, const char *path, size_t *size_out) {
  if (mount == 0 || file == 0 || path == 0 || !mount->mounted) {
    return false;
  }

  FILE *fp = fopen(path, "rb");
  if (fp == 0) {
    return false;
  }
  if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
    return false;
  }
  long sz = ftell(fp);
  if (sz < 0) {
    fclose(fp);
    return false;
  }
  if (fseek(fp, 0, SEEK_SET) != 0) {
    fclose(fp);
    return false;
  }

  file->opaque = fp;
  if (size_out != 0) {
    *size_out = (size_t)sz;
  }
  return true;
}

bool ff_port_read(ff_file_t *file, uint8_t *buf, size_t len, size_t *read_out) {
  if (file == 0 || file->opaque == 0 || buf == 0 || len == 0u) {
    return false;
  }
  FILE *fp = (FILE *)file->opaque;
  const size_t n = fread(buf, 1u, len, fp);
  if (read_out != 0) {
    *read_out = n;
  }
  return n > 0u;
}

void ff_port_close(ff_file_t *file) {
  if (file == 0 || file->opaque == 0) {
    return;
  }
  FILE *fp = (FILE *)file->opaque;
  fclose(fp);
  file->opaque = 0;
}
