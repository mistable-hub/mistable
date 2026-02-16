#ifndef TASK_H
#define TASK_H
#include "FreeRTOS.h"
typedef void (*TaskFunction_t)(void *);
BaseType_t xTaskCreate(TaskFunction_t pxTaskCode,const char * const pcName,const uint16_t usStackDepth,void * const pvParameters,UBaseType_t uxPriority,TaskHandle_t * const pxCreatedTask);
void vTaskDelay(TickType_t xTicksToDelay);
void vTaskDelete(TaskHandle_t xTaskToDelete);
void vTaskStartScheduler(void);
#endif
