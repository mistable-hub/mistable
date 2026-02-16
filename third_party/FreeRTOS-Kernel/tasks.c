#include "FreeRTOS.h"
#include "task.h"
#include <time.h>

static TickType_t s_ticks = 0;

BaseType_t xTaskCreate(TaskFunction_t pxTaskCode,
                       const char *const pcName,
                       const uint16_t usStackDepth,
                       void *const pvParameters,
                       UBaseType_t uxPriority,
                       TaskHandle_t *const pxCreatedTask) {
  (void)pxTaskCode;
  (void)pcName;
  (void)usStackDepth;
  (void)pvParameters;
  (void)uxPriority;
  if (pxCreatedTask) {
    *pxCreatedTask = NULL;
  }
  return pdPASS;
}

void vTaskDelay(const TickType_t xTicksToDelay) {
  (void)xTicksToDelay;
}

void vTaskDelayUntil(TickType_t *const pxPreviousWakeTime,
                     const TickType_t xTimeIncrement) {
  if (pxPreviousWakeTime) {
    *pxPreviousWakeTime += xTimeIncrement;
  }
}

void vTaskStartScheduler(void) {
}

TickType_t xTaskGetTickCount(void) {
  return s_ticks++;
}
