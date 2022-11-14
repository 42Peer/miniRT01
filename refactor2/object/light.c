#include "../include/minirt.h"

void	light(t_scene *scene, char **data)
{
	t_light *light;

// 파싱
	light = (t_light *)wrap_malloc(sizeof(t_light));
	light->origin = str_to_vec3(data[1]);
	light->light_color = str_to_vec3(data[2]);
	light->bright_ratio = a_to_d(data[3]);
	oadd(scene->light, object(light, LIGHT_POINT));
}
