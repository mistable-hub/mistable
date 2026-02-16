#ifndef OSD_H
#define OSD_H

#include <stddef.h>

void osd_init(void);
void osd_compose_line(char *line, size_t line_len, const char *text);

#endif
