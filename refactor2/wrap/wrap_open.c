#include "../include/wrap.h"

int open(const char *pathname, int flags)
{
	int fd;

	fd = open(pathname, flags);
	if (fd == -1)
	{
		perror("open() fail");
		exit(1);
	}
	return (fd);
}
