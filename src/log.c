#include "log.h"
#include "usb/usb_device_cdc.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define LOG_BUFFER_SIZE 4096

static char s_log_buf[LOG_BUFFER_SIZE];
static size_t s_log_head;
static size_t s_log_tail;

static size_t log_available(void) {
  if (s_log_head >= s_log_tail) {
    return s_log_head - s_log_tail;
  }
  return LOG_BUFFER_SIZE - (s_log_tail - s_log_head);
}

static void log_push_char(char c) {
  size_t next = (s_log_head + 1) % LOG_BUFFER_SIZE;
  if (next == s_log_tail) {
    s_log_tail = (s_log_tail + 1) % LOG_BUFFER_SIZE;
  }
  s_log_buf[s_log_head] = c;
  s_log_head = next;
}

void log_init(void) {
  s_log_head = 0;
  s_log_tail = 0;
}

void log_write(const char *msg) {
  if (!msg) {
    return;
  }
  while (*msg) {
    log_push_char(*msg++);
  }
}

void log_printf(const char *fmt, ...) {
  char tmp[256];
  va_list args;
  va_start(args, fmt);
  vsnprintf(tmp, sizeof(tmp), fmt, args);
  va_end(args);
  log_write(tmp);
}

void log_flush(void) {
  char out[256];
  while (log_available() > 0) {
    size_t count = 0;
    while (count < sizeof(out) - 1 && log_available() > 0) {
      out[count++] = s_log_buf[s_log_tail];
      s_log_tail = (s_log_tail + 1) % LOG_BUFFER_SIZE;
    }
    out[count] = '\0';
    usb_cdc_write(out, count);
  }
}
