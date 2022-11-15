#include "../include/minirt.h"
#include <string.h>             // <-       remove!!!!!!!!!

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

int	ft_strcmp(char *line, char *c)
{
	return (strcmp(line, c));
}

static void	free_split(char **data)
{
	char	**cur;

	cur = data;
	while (*cur)
	{
		free(*cur);
		cur++;
	}
	free(data);
}

static void unknown_object_error(void)
{
	perror("unknown_object");
	exit(1);
}



void object_parser(char **line, t_scene *scene)
{
	char **data;

	while (*line)
	{
		printf("line : %s\n", *line);
		data = ft_split(*line, ' ');
		line++;
	
		if (!ft_strcmp(data[0], "A"))
			ambient(scene, data);
		else if (!ft_strcmp(data[0], "L"))
			light(scene, data);
		else if (!ft_strcmp(data[0], "C"))
			camera(scene, data);
		else if (!ft_strcmp(data[0], "pl"))
			plane(scene, data);
		else if (!ft_strcmp(data[0], "sp"))
			sphere(scene, data);
		else if (!ft_strcmp(data[0], "cy"))
			cylinder(scene, data);
		else
			unknown_object_error();
		free_split(data);
	}
	
	while (*line)
	{
		printf("line : %s\n", *line);
		data = ft_split(*line, ' ');
		line++;

		if (!ft_strcmp(data[0], "A"))
			ambient(scene, data);
		else if (!ft_strcmp(data[0], "L"))
			light(scene, data);
		else if (!ft_strcmp(data[0], "C"))
			camera(scene, data);
		else if (!ft_strcmp(data[0], "pl"))
			plane(scene, data);
		else if (!ft_strcmp(data[0], "sp"))
			sphere(scene, data);
		else if (!ft_strcmp(data[0], "cy"))
			cylinder(scene, data);
		else
			unknown_object_error();
		free_split(data);
	}
}

char	**file_parser(char *filename)
{
	// t_scene	scene;
	int		fd;
	int		count;
	char	*raw_data;
	char	**line;

	// .rt 체크
	count = get_file_size(filename);
	fd = wrap_open(filename, O_RDONLY);
	raw_data = (char *)wrap_malloc(sizeof(char) * (count + 1));
	read(fd, raw_data, count);
	close(fd);
	line = ft_split(raw_data, '\n');
	return (line);
}

t_scene	parse(char *filename)
{
	t_scene	scene;
	char	**line;

	scene.light_list = 0;
	scene.object_list = 0;
	// ft_memset(&scene.light_list, 0, ft_strlen(scene.light_list));
	line = file_parser(filename);
	object_parser(line, &scene);
	return (scene);
}
