#ifndef FF_H
#define FF_H

#include <stdint.h>

typedef struct {
  int mounted;
} FATFS;

typedef struct {
  void *fp;
} FIL;

typedef uint32_t UINT;
typedef uint8_t BYTE;

typedef enum {
  FR_OK = 0,
  FR_DISK_ERR = 1,
  FR_NO_FILE = 2,
  FR_INVALID_OBJECT = 3
} FRESULT;

#define FA_READ 0x01

FRESULT f_mount(FATFS *fs, const char *path, int opt);
FRESULT f_open(FIL *file, const char *path, BYTE mode);
FRESULT f_read(FIL *file, void *buffer, UINT bytes_to_read, UINT *bytes_read);
FRESULT f_close(FIL *file);

#endif
