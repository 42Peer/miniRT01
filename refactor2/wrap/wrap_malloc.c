#include "../include/wrap.h"

void *wrap_malloc(size_t size)
{
	void *ret;

	ret = malloc(size);
	if (ret == NULL)
	{
		perror("malloc fail");
		exit (1);
	}
	return (ret);
}
