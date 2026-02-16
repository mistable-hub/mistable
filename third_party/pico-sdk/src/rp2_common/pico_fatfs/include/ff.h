#ifndef FF_H
#define FF_H

#include <stddef.h>
#include <stdint.h>

typedef uint32_t UINT;
typedef uint8_t BYTE;
typedef uint32_t DWORD;
typedef uint32_t LBA_t;
typedef size_t UINT_PTR;

typedef enum {
  FR_OK = 0,
  FR_DISK_ERR = 1,
  FR_INT_ERR = 2,
  FR_NOT_READY = 3,
  FR_NO_FILE = 4,
  FR_NO_PATH = 5,
  FR_INVALID_NAME = 6,
  FR_DENIED = 7,
  FR_EXIST = 8,
  FR_INVALID_OBJECT = 9,
  FR_WRITE_PROTECTED = 10,
  FR_INVALID_DRIVE = 11,
  FR_NOT_ENABLED = 12,
  FR_NO_FILESYSTEM = 13,
  FR_MKFS_ABORTED = 14,
  FR_TIMEOUT = 15,
  FR_LOCKED = 16,
  FR_NOT_ENOUGH_CORE = 17,
  FR_TOO_MANY_OPEN_FILES = 18,
  FR_INVALID_PARAMETER = 19
} FRESULT;

typedef struct {
  int dummy;
} FATFS;

typedef struct {
  int dummy;
  uint32_t fsize;
} FIL;

FRESULT f_mount(FATFS *fs, const char *path, uint8_t opt);
FRESULT f_open(FIL *fp, const char *path, uint8_t mode);
FRESULT f_read(FIL *fp, void *buff, UINT btr, UINT *br);
FRESULT f_close(FIL *fp);
FRESULT f_stat(const char *path, void *fno);

#define FA_READ 0x01

#endif
