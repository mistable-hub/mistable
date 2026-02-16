#include "FreeRTOS.h"
#include <stddef.h>

void *pvPortMalloc(size_t xSize) { (void)xSize; return 0; }
void vPortFree(void *pv) { (void)pv; }
