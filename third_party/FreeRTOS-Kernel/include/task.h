#ifndef TASK_H
#define TASK_H

#include "FreeRTOS.h"

typedef void (*TaskFunction_t)(void *);
typedef void * TaskHandle_t;

BaseType_t xTaskCreate(TaskFunction_t task_code,
                       const char * const name,
                       uint16_t stack_depth,
                       void * params,
                       UBaseType_t priority,
                       TaskHandle_t * created_task);
void vTaskStartScheduler(void);
void vTaskDelay(TickType_t ticks);

#endif
