#include "./include/minirt.h"

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

int main(int argc, char **argv)
{
	t_scene	scene;
	// printf("hello world!\n");
	scene = parse(argv[1]);
	//scene.light_list = 0;
	printf_test(&scene);
}

/*
struct s_scene
{
	t_mlx			mlx;
	t_camera		camera;
	t_object		*object_list;
	t_object		*light_list;
	t_ambient 		ambient;
	t_ray			ray;			// camera -> viewport
	t_hit_record	rec;			// ray가 만난 교점(hit)의 정보
};
*/