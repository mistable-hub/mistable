#ifndef FREERTOS_H
#define FREERTOS_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define pdPASS 1
#define pdTRUE 1
#define pdFALSE 0
#define pdMS_TO_TICKS(ms) (ms)
typedef int BaseType_t;
typedef unsigned int UBaseType_t;
typedef uint32_t TickType_t;
typedef void * TaskHandle_t;
#endif
