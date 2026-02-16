#include "ff.h"

#include <stdio.h>

FRESULT f_mount(FATFS *fs, const char *path, int opt) {
  (void)path;
  (void)opt;
  if (!fs) {
    return FR_DISK_ERR;
  }
  fs->mounted = 1;
  return FR_OK;
}

FRESULT f_open(FIL *file, const char *path, BYTE mode) {
  (void)mode;
  if (!file) {
    return FR_INVALID_OBJECT;
  }
  FILE *fp = fopen(path, "rb");
  if (!fp) {
    return FR_NO_FILE;
  }
  file->fp = fp;
  return FR_OK;
}

FRESULT f_read(FIL *file, void *buffer, UINT bytes_to_read, UINT *bytes_read) {
  if (!file || !file->fp) {
    return FR_INVALID_OBJECT;
  }
  size_t n = fread(buffer, 1, bytes_to_read, (FILE *)file->fp);
  if (bytes_read) {
    *bytes_read = (UINT)n;
  }
  return FR_OK;
}

FRESULT f_close(FIL *file) {
  if (!file || !file->fp) {
    return FR_INVALID_OBJECT;
  }
  fclose((FILE *)file->fp);
  file->fp = NULL;
  return FR_OK;
}
