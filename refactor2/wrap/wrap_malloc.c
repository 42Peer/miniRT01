#include "../include/wrap.h"

void	*wrap_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		exit_with_error("memory allocation failed\n");
	return (ret);
}
