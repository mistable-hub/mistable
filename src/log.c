#include "log.h"

#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define LOG_RING_SIZE 16384

static char ring[LOG_RING_SIZE];
static size_t wpos;
static size_t rpos;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void log_init(void) {
  pthread_mutex_lock(&lock);
  wpos = 0;
  rpos = 0;
  memset(ring, 0, sizeof(ring));
  pthread_mutex_unlock(&lock);
}

void log_printf(const char *fmt, ...) {
  char line[512];
  va_list args;
  va_start(args, fmt);
  int n = vsnprintf(line, sizeof(line), fmt, args);
  va_end(args);
  if (n <= 0) {
    return;
  }
  size_t to_write = (size_t)n;
  if (to_write >= sizeof(line)) {
    to_write = sizeof(line) - 1;
  }

  pthread_mutex_lock(&lock);
  for (size_t i = 0; i < to_write; ++i) {
    ring[wpos] = line[i];
    wpos = (wpos + 1u) % LOG_RING_SIZE;
    if (wpos == rpos) {
      rpos = (rpos + 1u) % LOG_RING_SIZE;
    }
  }
  if (to_write == 0 || line[to_write - 1] != '\n') {
    ring[wpos] = '\n';
    wpos = (wpos + 1u) % LOG_RING_SIZE;
    if (wpos == rpos) {
      rpos = (rpos + 1u) % LOG_RING_SIZE;
    }
  }
  pthread_mutex_unlock(&lock);
}

size_t log_pop(char *out, size_t out_size) {
  if (!out || out_size == 0) {
    return 0;
  }
  pthread_mutex_lock(&lock);
  size_t n = 0;
  while (rpos != wpos && n < out_size) {
    out[n++] = ring[rpos];
    rpos = (rpos + 1u) % LOG_RING_SIZE;
  }
  pthread_mutex_unlock(&lock);
  return n;
}
