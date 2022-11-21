#include "../include/minirt.h"

void	sphere(t_scene *scene, char **data)
{
	t_sphere	*sphere;

	sphere = wrap_malloc(sizeof(t_sphere));
	sphere->center = str_to_vec3(data[1]);
	sphere->radius = a_to_d(data[2]) / 2;
	sphere->radius_pow_2 = pow(sphere->radius, 2);
	sphere->color = parse_color(data[3]);
	oadd(&(scene->object_list), object(sphere, SP));
}
