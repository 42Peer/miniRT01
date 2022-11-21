#ifndef WRAP_H
# define WRAP_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/syslimits.h>
# include "minirt.h"

void	*wrap_malloc(size_t size);
int		wrap_open(const char *pathname, int flags);

#endif
