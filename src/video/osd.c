#include "osd.h"

#include <stdio.h>

void osd_init(void) {
}

void osd_compose_line(char *line, size_t line_len, const char *text) {
  if (line_len == 0) {
    return;
  }
  (void)snprintf(line, line_len, "%s", text);
}
