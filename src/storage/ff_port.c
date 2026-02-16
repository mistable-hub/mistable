#include "ff_port.h"

#include "ff.h"

static FATFS g_fs;

int ff_port_mount(void) {
  return f_mount(&g_fs, "", 1) == FR_OK ? 0 : -1;
}
