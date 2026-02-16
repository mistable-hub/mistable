#include "log.h"

#include <string.h>

#define LOG_CAPACITY 8192

static char g_ring[LOG_CAPACITY];
static size_t g_head;
static size_t g_tail;

void log_init(void) {
  g_head = 0;
  g_tail = 0;
}

void log_write(const char *msg) {
  if (msg == 0) {
    return;
  }
  for (size_t i = 0; msg[i] != '\0'; ++i) {
    size_t next = (g_head + 1u) % LOG_CAPACITY;
    if (next == g_tail) {
      break;
    }
    g_ring[g_head] = msg[i];
    g_head = next;
  }
}

bool log_pop(char *out, size_t out_len) {
  size_t n = 0;
  if (out_len == 0) {
    return false;
  }
  while (g_tail != g_head && n + 1 < out_len) {
    char c = g_ring[g_tail];
    g_tail = (g_tail + 1u) % LOG_CAPACITY;
    out[n++] = c;
    if (c == '\n') {
      break;
    }
  }
  out[n] = '\0';
  return n > 0;
}
