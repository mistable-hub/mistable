#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define LOG_RING_SIZE 8192

static char g_ring[LOG_RING_SIZE];
static size_t g_head;
static size_t g_tail;

void log_init(void) {
  g_head = 0;
  g_tail = 0;
}

static void ring_push_char(char c) {
  const size_t next = (g_head + 1u) % LOG_RING_SIZE;
  if (next == g_tail) {
    g_tail = (g_tail + 1u) % LOG_RING_SIZE;
  }
  g_ring[g_head] = c;
  g_head = next;
}

void log_write(const char *msg) {
  if (msg == NULL) {
    return;
  }
  while (*msg != '\0') {
    ring_push_char(*msg++);
  }
}

void log_printf(const char *fmt, ...) {
  char line[256];
  va_list ap;
  va_start(ap, fmt);
  const int n = vsnprintf(line, sizeof(line), fmt, ap);
  va_end(ap);
  if (n <= 0) {
    return;
  }
  line[sizeof(line) - 1u] = '\0';
  log_write(line);
}

bool log_try_pop_line(char *out, size_t out_size) {
  if (out == NULL || out_size == 0u || g_tail == g_head) {
    return false;
  }

  size_t idx = 0;
  while (g_tail != g_head && idx + 1u < out_size) {
    const char c = g_ring[g_tail];
    g_tail = (g_tail + 1u) % LOG_RING_SIZE;
    out[idx++] = c;
    if (c == '\n') {
      break;
    }
  }
  out[idx] = '\0';
  return idx > 0u;
}
