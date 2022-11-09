#include "trace.h"

t_hit_record	record_init(void)
{
	t_hit_record	record;

	record.tmin = EPSILON;
	record.tmax = INFINITY;
	return (record);
}

// ray 생성자
t_ray	ray(t_point3 orig, t_vec3 dir)
{
	t_ray ray;

	ray.orig = orig;
	ray.dir = vunit(dir);
	return (ray);
}

// ray origin point부터 방향벡터 ray dir * t 만큼 떨어진  점.
t_point3 ray_at(t_ray *ray, double t)
{
	t_point3 at;

	at = vplus(ray->orig, vmult(ray->dir, t));
	return (at);
}

t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.orig = cam->orig;
	// 카메라->뷰포트의 단위벡터
	ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
	return (ray);
}

t_color3	ray_color(t_scene *scene)
{
	double	t;
	// t_vec3	n;

	// 광선이 구를 만남(광선과 구의 교점 존재, 교점이 카메라 앞쪽)
	scene->rec = record_init();
	if (hit(scene->world, &scene->ray, &scene->rec))
		return (phong_lighting(scene));
	else
	{
		t = 0.5 * (scene->ray.dir.y + 1.0);
		return (vplus(vmult(color3(1,1,1), 1.0-t), vmult(color3(0.5, 0.7, 1.0), t)));
	}
}
	