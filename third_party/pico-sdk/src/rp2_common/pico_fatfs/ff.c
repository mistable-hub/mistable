#include "ff.h"

FRESULT f_mount(FATFS *fs, const char *path, uint8_t opt) {
  (void)fs;
  (void)path;
  (void)opt;
  return FR_DISK_ERR;
}

FRESULT f_open(FIL *fp, const char *path, uint8_t mode) {
  (void)fp;
  (void)path;
  (void)mode;
  return FR_NO_FILE;
}

FRESULT f_read(FIL *fp, void *buff, UINT btr, UINT *br) {
  (void)fp;
  (void)buff;
  (void)btr;
  if (br) {
    *br = 0;
  }
  return FR_DISK_ERR;
}

FRESULT f_close(FIL *fp) {
  (void)fp;
  return FR_OK;
}

FRESULT f_stat(const char *path, void *fno) {
  (void)path;
  (void)fno;
  return FR_NO_FILE;
}
