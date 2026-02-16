#include "log.h"

#include <stdio.h>
#include <string.h>

#define LOG_BUF_SZ 4096

static char g_log_buf[LOG_BUF_SZ];
static size_t g_head;
static size_t g_tail;

void log_init(void) {
  g_head = 0;
  g_tail = 0;
}

static void push_char(char c) {
  size_t next = (g_head + 1u) % LOG_BUF_SZ;
  if (next == g_tail) {
    g_tail = (g_tail + 1u) % LOG_BUF_SZ;
  }
  g_log_buf[g_head] = c;
  g_head = next;
}

void log_printf(const char *fmt, ...) {
  char line[256];
  va_list ap;
  va_start(ap, fmt);
  int n = vsnprintf(line, sizeof(line), fmt, ap);
  va_end(ap);
  if (n <= 0) {
    return;
  }
  size_t len = (size_t)n;
  if (len > sizeof(line) - 1u) {
    len = sizeof(line) - 1u;
  }
  for (size_t i = 0; i < len; ++i) {
    push_char(line[i]);
  }
}

size_t log_drain(char *out, size_t out_len) {
  size_t n = 0;
  while (g_tail != g_head && n < out_len) {
    out[n++] = g_log_buf[g_tail];
    g_tail = (g_tail + 1u) % LOG_BUF_SZ;
  }
  return n;
}

bool log_has_data(void) {
  return g_head != g_tail;
}
