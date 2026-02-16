#include "log.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define LOG_RING_SIZE 4096

static char ring[LOG_RING_SIZE];
static volatile uint32_t head;
static volatile uint32_t tail;

void log_init(void) {
  head = 0;
  tail = 0;
}

static void log_push(const char *s, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    uint32_t next = (head + 1u) % LOG_RING_SIZE;
    if (next == tail) {
      tail = (tail + 1u) % LOG_RING_SIZE;
    }
    ring[head] = s[i];
    head = next;
  }
}

void log_printf(const char *fmt, ...) {
  char tmp[256];
  va_list ap;
  va_start(ap, fmt);
  int n = vsnprintf(tmp, sizeof(tmp), fmt, ap);
  va_end(ap);
  if (n <= 0) return;
  size_t len = (size_t)n;
  if (len >= sizeof(tmp)) {
    len = sizeof(tmp) - 1;
  }
  log_push(tmp, len);
}

size_t log_read_chunk(char *dst, size_t max_len) {
  size_t out = 0;
  while (tail != head && out < max_len) {
    dst[out++] = ring[tail];
    tail = (tail + 1u) % LOG_RING_SIZE;
  }
  return out;
}

bool log_has_data(void) {
  return head != tail;
}
