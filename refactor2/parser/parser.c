#include "../include/minirt.h"

void object_parser(char **line, t_scene *scene)
{
	char **data;
	
	while (line)
	{
		data = ft_split(line, ' ');
		line++;
	
		if (ft_strcmp(data[0], "A"))
			ambient(scene, data);
			// scene->ambient = create_ambient(data);
		else if (ft_strcmp(data[0], "L"))
			light(scene, data);
			//oadd(&scene->light_list, object(light_point(data), LIGHT_POINT));
		else if (ft_strcmp(data[0], "C"))
			camera(scene, data);
		else if (ft_strcmp(data[0], "pl"))
			plane(scene, data);
		else if (ft_strcmp(data[0], "sp"))
			sphere(scene, data);
		else if (ft_strcmp(data[0], "cy"))
			cylinder(scene, data);
		else
			에러처리(); -> exit();
		free_data(...);
	}
}

char	**file_parser(char *filename)
{
	t_scene	scene;
	int		fd;
	int		count;
	char	*raw_data;
	char	**line;

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

	line = file_parser(filename);
	object_parser(line, &scene);
	return (scene);
}
