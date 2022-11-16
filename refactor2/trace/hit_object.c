#include "../include/minirt.h"

t_bool	set_root(double a, double half_b, double c, t_hit_record *rec)
{
	double	root;
	double	discriminant;
	double	sqrtd;

	// 두 실근(t) 중 tmin:0과 tmax:INFF 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
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
	return (TRUE);
}

t_bool hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere *sp;

	t_vec3  oc; //방향벡터로 나타낸 구의 중심, oc = origin - center
	//a, b, c는 각각 t에 관한 2차 방정식의 계수
	double  a; // D dot D
	double  half_b;
	double  c; // (O - C) dot (O - C) - R^2

	sp = sp_obj->element;
	oc = vminus(ray->orig, sp->center);

	a = vlength2(ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius_pow_2;

	if (!set_root(a, half_b, c, rec))
		return (FALSE);
	rec->p = ray_at(ray, rec->t);
	rec->color = sp->color;
	rec->normal = vunit(vminus(rec->p, sp->center));
	set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장.
	return (TRUE);
}

t_bool	hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
	t_plane	*pl;
	double denominator;
	double numerator;
	double root;

	pl = pl_obj->element;
	denominator = vdot(pl->normal, ray->dir);
	if (fabs(denominator) < EPSILON)
		return (FALSE);
	numerator = vdot(vminus(pl->center, ray->orig), pl->normal);
	root = numerator / denominator;

	// tmin:0과 tmax:INFF 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
	if (root < rec->tmin || rec->tmax < root) 
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->color = pl->color;
	rec->normal = pl->normal;
	set_face_normal(ray, rec);
	return (TRUE);
}

//t_bool hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
//{
//	t_cylinder *cy;

//	t_vec3  oc; //방향벡터로 나타낸 구의 중심, oc = origin - center
//	double  a; // D dot D
//	double  half_b;
//	double  c; // (O - C) dot (O - C) - R^2

//	cy = cy_obj->element;

//	oc = vminus(ray->orig, cy->point);
//	a = vlength2(ray->dir);
//	half_b = vdot(oc, ray->dir);
//	c = vlength2(oc) - cy->radius_pow_2;

//	if (!set_root(a, half_b, c, rec))
//		return (FALSE);
//	rec->p = ray_at(ray, rec->t);
//	rec->color = cy->color;
//	rec->normal = vunit(vminus(rec->p, cy->point));
//	set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장.
//	return (TRUE);
//}