#ifndef FREERTOS_H
#define FREERTOS_H

#include <stdint.h>

#define pdTRUE 1
#define pdFALSE 0
#define pdPASS 1
#define pdFAIL 0

typedef int BaseType_t;
typedef unsigned int UBaseType_t;
typedef uint32_t TickType_t;

typedef void * TaskHandle_t;

typedef void (*TaskFunction_t)(void *);

#define configTICK_RATE_HZ 1000

#define pdMS_TO_TICKS(x) ((TickType_t)((x) * (configTICK_RATE_HZ / 1000.0f)))

#endif
