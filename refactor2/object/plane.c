#include "../include/minirt.h"

void	plane(t_scene *scene, char **data)
{
	t_plane	*plane;

	plane = wrap_malloc(sizeof(t_plane));
	plane->center = str_to_vec3(data[1]);
	plane->normal = vunit(str_to_vec3(data[2]));
	plane->color = parse_color(data[3]);
	plane->texture.img = mlx_xpm_file_to_image(scene->mlx.mlx, "./asset/bumpmap.xpm", &plane->texture.img_w, &plane->texture.img_h);
	plane->texture.addr = mlx_get_data_addr(plane->texture.img, &plane->texture.bits_per_pixel, \
		&plane->texture.line_length, &plane->texture.endian);
	oadd(&scene->object_list, object(plane, PL));
}
