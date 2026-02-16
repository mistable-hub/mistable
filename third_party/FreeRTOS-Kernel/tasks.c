#include "task.h"

#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define MAX_TASKS 8

typedef struct {
  TaskFunction_t fn;
  void *param;
  pthread_t thread;
  int used;
} task_slot_t;

static task_slot_t slots[MAX_TASKS];

static void *task_trampoline(void *arg) {
  task_slot_t *slot = (task_slot_t *)arg;
  slot->fn(slot->param);
  return NULL;
}

BaseType_t xTaskCreate(TaskFunction_t task_code,
                       const char * const name,
                       uint16_t stack_depth,
                       void * params,
                       UBaseType_t priority,
                       TaskHandle_t * created_task) {
  (void)name;
  (void)stack_depth;
  (void)priority;
  (void)created_task;

  for (int i = 0; i < MAX_TASKS; ++i) {
    if (!slots[i].used) {
      slots[i].used = 1;
      slots[i].fn = task_code;
      slots[i].param = params;
      if (pthread_create(&slots[i].thread, NULL, task_trampoline, &slots[i]) != 0) {
        slots[i].used = 0;
        return pdFAIL;
      }
      return pdPASS;
    }
  }
  return pdFAIL;
}

void vTaskStartScheduler(void) {
  for (;;) {
    pause();
  }
}

void vTaskDelay(TickType_t ticks) {
  struct timespec ts;
  ts.tv_sec = ticks / 1000;
  ts.tv_nsec = (long)(ticks % 1000) * 1000000L;
  nanosleep(&ts, NULL);
}
