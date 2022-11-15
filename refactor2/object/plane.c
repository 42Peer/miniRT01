/*
struct s_plane 
{
	t_point3	center;	// 평면 내의 한 점
	t_vec3		normal;	// 평면의 법선 벡터
	t_color3	color;	// 색상
};
*/

#include "../include/minirt.h"

void	plane(t_scene *scene, char **data)
{
	t_plane *plane;

	//check_data();

// 파싱
	plane = (t_plane *)wrap_malloc(sizeof(t_plane));
	plane->center = str_to_vec3(data[1]);
	// invalid : (3차원 좌표계 백터의 크기 != 1) error
	plane->normal = str_to_vec3(data[2]);
	plane->color = str_to_vec3(data[3]);
	oadd(&scene->object_list, object(plane, PL));
}

// pl     0.0,0.0,-10.0    0.0,1.0,0.0     0,0,225