#ifndef WRAP_H
#define WRAP_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/syslimits.h>

void *wrap_malloc(size_t size);
int open(const char *pathname, int flags);

#endif
