
#include "minirt.h"

void        oadd(t_object **list, t_object *new_obj)
{
    t_object    *cur;

    if (*list == NULL)
    {
        *list = new_obj;
        return ;
    }
    cur = *list;
    while (cur->next)
        cur = cur->next;
    cur->next = new_obj;
}

void	light(t_scene *scene, char **data)
{
    t_light *light;

// 파싱
    if(!(light = (t_light *)malloc(sizeof(t_light))))
        return (NULL);
    light->origin = light_origin;
    light->light_color = light_color;
    light->bright_ratio = bright_ratio;
    return (light);
}

t_object	*object(void *object, t_object_type type)
{
	t_object	*obj;

	obj = wrap_malloc(sizeof(t_object));
	obj->element = object;
	obj->type = type;
	obj->next = 0;
	return (obj);
}

t_ambient ambient(t_scene *scene, char **data)
{
	t_ambient ambient;

	ambient.ambient = a_to_d(data[1]);
	ambient.color = parse_color(data[2]);
}

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
	raw_data = (char *)malloc(sizeof(char) * (count + 1));
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
