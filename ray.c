#include "./trace.h"

// ray 생성자 정규화된 ray
t_ray	ray(t_point3 orig, t_vec3 dir)
{
	t_ray	ray;

	ray.orig = orig;
	ray.dir = vunit(dir);
	return (ray);
}

// ray 원점부터 방향 벡터 ray dir * t 만큼 떨어진점
t_point3 ray_at(t_ray *ray, double t)
{
	t_point3	at;

	at = vplus(ray->orig, vmult(ray->dir, t));
	return (at);
}

// primary_ray 생성자
t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.orig = cam->orig;
	// left_bottom + u*horizontal + v*vertical - origin 의 단위벡터 
    ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
	return (ray);
}

t_hit_record	record_init(void)
{
	t_hit_record	record;

	record.tmin = EPSILON;
	record.tmax = INFINITY;
	return (record);
}

t_color3	ray_color(t_scene *scene)
{
	double			t;
	t_vec3			n;

	//광선이 구에 적중하면(광선과 구가 교점이 있고, 교점이 카메라 앞쪽이라면!)
	scene->rec = record_init();
	if (hit(scene->world, &scene->ray, &scene->rec))
		return (phong_lighting(scene)); //phong_lighting 함수를 통해서 매핑할것이다 이제 법선백테로 매핑안한다!
	else
	{
		// ray의 방향벡터의 y 값을 기준으로 그라데이션을 주기 위한 계쑤.
		t = 0.5 * (scene->ray.dir.y + 1.0);
		// (1-t) * 흰색 + t * 하늘색
		return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t)));
	}
}


// t_color3	ray_color(t_scene *scene)
// {
// 	double			t;
// 	t_vec3			n;
// 	t_hit_record	rec;

// 	rec.tmin = 0;
// 	rec.tmax = INFINITY;
// 	if (hit(scene->world, ray, &rec))
// 		return (vmult(vplus(rec.normal, color3(1, 1, 1)), 0.5));
// 	else
// 	{
// 		// ray 의 방향벡터 y 값을 기준으로 그라데이션을 주기 위한 계수
// 		t = 0.5 * (scene->ray.dir.y + 1.0);
// 		// (1-t) * white + t * sky
// 		return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t)));
// 	}
// }
