#include "include/structures.h"
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int	wrap_open(char *filename, int oflag);
void *wrap_malloc(size_t size);
int	get_file_size(char *filename);
