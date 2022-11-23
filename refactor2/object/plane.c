#include "../include/minirt.h"

void	plane(t_scene *scene, char **data)
{
	t_plane	*plane;

	plane = wrap_malloc(sizeof(t_plane));
	plane->center = str_to_vec3(data[1]);
	plane->normal = vunit(str_to_vec3(data[2]));
	plane->color = parse_color(data[3]);
	oadd(&scene->object_list, object(plane, PL));
}
