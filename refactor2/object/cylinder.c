/*
struct s_cylinder
{
	t_point3	point;	// todo: 원기둥의 한 점? 근데 어디 한점?????????
	t_vec3		normal; // 법선벡터
	t_color3	color;	// RGB
	double		radius; // 밑면의 반지름 = diameter / 2
	double		height; // 원기둥의 높이
};
*/

// cy    50.0,0.0,20.6     0.0,0.0,1.0       14.2    21.42     10,0,255
//           xyz     normalized vector     diameter  height       rgb

#include "../include/minirt.h"

void	cylinder(t_scene *scene, char **data)
{
	t_cylinder *cylinder;

	// check_data();
	
	// 파싱
	cylinder = (t_cylinder *)wrap_malloc(sizeof(t_cylinder));
	cylinder->point = str_to_vec3(data[1]);
	cylinder->normal = str_to_vec3(data[2]);
	cylinder->radius = a_to_d(data[3]) / 2;
	cylinder->height = a_to_d(data[4]);
	cylinder->color = parse_color(data[5]);
	oadd(&scene->object_list, object(cylinder, CY));
}
