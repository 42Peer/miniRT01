#include "../include/wrap.h"

int	wrap_open(const char *pathname, int flags)
{
	int	fd;

	fd = open(pathname, flags);
	if (fd == -1)
		exit_with_error("file open fail\n");
	return (fd);
}
