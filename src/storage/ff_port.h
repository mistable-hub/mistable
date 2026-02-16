#ifndef FF_PORT_H
#define FF_PORT_H

#include <stdbool.h>

bool ff_port_mount(void);
bool ff_port_read_file(const char *path, void *dst, unsigned *size_inout);

#endif
