/*
struct s_sphere 
{
	t_point3	center;			// 원의 중심
	double		radius;			// 반지름 = diameter / 2
	double		radius_pow_2;	// 반지름^2
	t_color3	color;			// 색상
};
*/

// sp    0.0,0.0,20.6    12.6      10,0,255


#include "../include/minirt.h"

void	sphere(t_scene *scene, char **data)
{
	t_sphere *sphere;

	//check_data();

    // 파싱
	sphere = wrap_malloc(sizeof(t_sphere));
	sphere->center = str_to_vec3(data[1]);
	sphere->radius = a_to_d(data[2]) / 2;
	sphere->radius_pow_2 = pow(sphere->radius, 2);
	sphere->color = str_to_vec3(data[3]);
	oadd(&(scene->object_list), object(sphere, SP));
}

// pl     0.0,0.0,-10.0    0.0,1.0,0.0     0,0,225