#include "structures.h"
#include "utils.h"
#include "trace.h"

// double	hit_sphere(t_sphere *sp, t_ray *ray)
// {
// 	t_vec3	oc; // 방향벡터로 나타낸 구의 중심
// 	// a, b, c 는 각각 t에 관한 2차 방정식의 계수
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	discriminant; // 판별식

// 	oc = vminus(ray->orig, sp->center);
// 	a = vdot(ray->dir, ray->dir);
// 	b = 2.0 * vdot(oc, ray->dir);
// 	c = vdot(oc, oc) - sp->radius_pow_2;
// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 		return (-1.0);
// 	else
// 		return ((-b - sqrt(discriminant)) / (2.0 * a));
// }

t_bool	hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_vec3	oc; // 방향벡터로 나타낸 구의 중심
	// a, b, c 는 각각 t에 관한 2차 방정식의 계수
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;
	t_sphere *sp;

	sp = (t_sphere*)(sp_obj->element);
	oc = vminus(ray->orig, sp->center);
	a = vlength2(ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius_pow_2;
	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	set_face_normal(ray, rec);
	rec->albedo = sp_obj->albedo;
	return (TRUE);
}