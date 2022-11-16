#include "../include/minirt.h"

void	light(t_scene *scene, char **data)
{
	t_light *light;

//printf("data1 %ld\ndata2%ld\n data3%ld\n",data[1] ,data[2],data[3]);
// 파싱
	light = wrap_malloc(sizeof(t_light));
	light->origin = str_to_vec3(data[1]);
	light->bright_ratio = a_to_d(data[2]);
	// light->light_color = str_to_vec3(data[3]);
	light->light_color = vec3(255, 255, 255);
	oadd(&(scene->light_list), object(light, LIGHT_POINT));
}
