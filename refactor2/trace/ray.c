#include "../include/minirt.h"

// ray = o + dt
t_ray	ray(t_point3 orig, t_vec3 dir)
{
    t_ray ray;

    ray.orig = orig;
    ray.dir = vunit(dir);
    return (ray);
}

t_point3    ray_at(t_ray *ray, double t)
{
    t_point3 at;

    at = vplus(ray->orig, vmult_k(ray->dir, t));
    return (at);
}

t_hit_record record_init(void)
{
    t_hit_record    record;

    record.tmin = EPSILON;
    record.tmax = INFINITY;
    return (record);
}

t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.orig = cam->orig;
	// left_top + u * horizontal + v * vertical - origin 의 단위 벡터.
	ray.dir = vunit(vminus(vplus(vplus(cam->left_top, vmult_k(cam->horizontal, u)), vmult_k(cam->vertical, v)), cam->orig));
	return (ray);
}

t_color3    ray_color(t_scene *scene)
{
    // double          t;

    //광선이 구에 적중하면(광선과 구가 교점이 있고, 교점이 카메라 앞쪽이라면!)
    scene->rec = record_init();
    if (hit(scene->object_list, &scene->ray, &scene->rec))
        return (phong_lighting(scene)); 
    else
		return (color3(0, 0, 0));
}