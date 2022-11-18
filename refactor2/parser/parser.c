#include "../include/minirt.h"

void	printf_vec(t_vec3 v)
{
	printf("x: %lf y: %lf z: %lf\n", v.x, v.y, v.z);
}

void	printf_camera(t_camera camera)
{
	printf("[camera]\n");
	printf("orig : ");
	printf_vec(camera.orig);
	printf("camera_dir : ");
	printf_vec(camera.camera_dir);
}

void	printf_ambient(t_ambient ambient)
{
	printf("[ambient]\n");
	printf("ambient : %lf\n", ambient.ambient);
	printf("color : ");
	printf_vec((t_vec3)ambient.color);
	printf("\n");
}

void	printf_light(t_light light)
{
	printf("[light]\n");
	printf("origin : ");
	printf_vec(light.origin);
	printf("color : ");
	printf_vec((t_vec3)light.light_color);
	printf("bright_ratio : %lf\n", light.bright_ratio);
	printf("\n");
}


void	printf_cylinder(t_cylinder cylinder)
{
	printf("[cylinder]\n");
	printf("point : ");
	printf_vec(cylinder.point);
	printf("normal : ");
	printf_vec(cylinder.normal);
	printf("color : ");
	printf_vec(cylinder.color);
	printf("radius : ");
	printf("%lf\n", cylinder.radius);
	printf("height : ");
	printf("%lf\n", cylinder.height);
}

void	printf_sphere(t_sphere sphere)
{
	printf("[sphere]\n");
	printf("center : ");
	printf_vec(sphere.center);
	printf("radius : ");
	printf("%lf\n", sphere.radius);
	printf("radius_pow_2 : ");
	printf("%lf\n", sphere.radius_pow_2);
	printf("color : ");
	printf_vec(sphere.color);
	printf("\n");
}

void	printf_plane(t_plane plane)
{
	printf("[plane]\n");
	printf("center point : ");
	printf_vec(plane.center);
	printf("normalized oriented : ");
	printf_vec(plane.normal);
	printf("color : ");
	printf_vec(plane.color);
	printf("\n");

}

void	printf_list(t_object *obj)
{
	t_object *cur;
	cur = obj;
	while (cur)
	{
		if (cur->type == CY)
			printf_cylinder(*(t_cylinder *)cur->element);
		else if (cur->type == SP)
			printf_sphere(*(t_sphere *)cur->element);
		else if (cur->type == LIGHT_POINT)
			printf_light(*(t_light *)cur->element);
		else if (cur->type == PL)
			printf_plane(*(t_plane *)cur->element);

		cur = cur->next;
	}
}

void	printf_test(t_scene *scene)
{
	printf("-------------< scene >-------------\n");
	// printf("[mlx]\n");
	printf_camera(scene->camera);
	printf_ambient(scene->ambient);
	printf("\n[object]\n");
	printf_list(scene->object_list);
	printf_list(scene->light_list);
	printf("-------------< end test >-------------\n");
}






void object_parser(char **line, t_scene *scene)
{
	char **data;

	while (*line)
	{
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
		free_split(data);
	}
}

char	**file_parser(char *filename)
{
	int		fd;
	int		count;
	char	*raw_data;
	char	**line;

	count = get_file_size(filename);
	fd = wrap_open(filename, O_RDONLY);
	raw_data = (char *)wrap_malloc(sizeof(char) * (count + 1));
	read(fd, raw_data, count);
	raw_data[count] = '\0';
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
	line = file_parser(filename);
	object_parser(line, &scene);
	// printf_test(&scene);
	return (scene);
}
