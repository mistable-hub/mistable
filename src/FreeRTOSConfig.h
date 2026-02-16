#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION 1
#define configUSE_16_BIT_TICKS 0
#define configCPU_CLOCK_HZ 150000000
#define configTICK_RATE_HZ 1000
#define configMAX_PRIORITIES 5
#define configMINIMAL_STACK_SIZE 256
#define configTOTAL_HEAP_SIZE (32 * 1024)
#define configMAX_TASK_NAME_LEN 16
#define configUSE_TRACE_FACILITY 0
#define configUSE_MUTEXES 0
#define configQUEUE_REGISTRY_SIZE 0
#define configUSE_RECURSIVE_MUTEXES 0
#define configUSE_MALLOC_FAILED_HOOK 0
#define configCHECK_FOR_STACK_OVERFLOW 0

#endif
