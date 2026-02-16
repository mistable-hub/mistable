#include "task.h"
#include <stdio.h>
#define MAX_TASKS 8
static TaskFunction_t g_tasks[MAX_TASKS];
static void *g_params[MAX_TASKS];
static int g_count = 0;
BaseType_t xTaskCreate(TaskFunction_t fn,const char * const name,const uint16_t stack,void * const param,UBaseType_t pri,TaskHandle_t * const out) {
  (void)name;(void)stack;(void)pri;(void)out;
  if (g_count >= MAX_TASKS) return !pdPASS;
  g_tasks[g_count] = fn;
  g_params[g_count] = param;
  g_count++;
  return pdPASS;
}
void vTaskDelay(TickType_t t) {(void)t;}
void vTaskDelete(TaskHandle_t task) {(void)task;}
void vTaskStartScheduler(void) {
  for (int i = 0; i < g_count; ++i) {
    g_tasks[i](g_params[i]);
  }
}
