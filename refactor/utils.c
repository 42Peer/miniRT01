#include "minirt.h"

int	wrap_open(char *filename, int oflag)
{
	int	fd;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(1);
	return (fd);
}

void *wrap_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		exit(1);
	return (ret);
}

int	get_file_size(char *filename)
{
	int		count;
	int		fd;
	int		read_byte;
	char	buff[1024];

	read_byte = 1;
	count = 0;
	fd = wrap_open(filename, O_RDONLY);
	while (read_byte)
	{
		read_byte = read(fd, buff, 1024);
		count += read_byte;
	}
	close(fd);
	return (count);
}