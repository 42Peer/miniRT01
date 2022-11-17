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
t_bool	hit_circle(t_cylinder *cy, t_ray *ray, t_hit_record *rec);

t_bool hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder const *cy = cy_obj->element;
	const t_vec3  uo_c = vcross(ray->dir, cy->normal);
	const t_vec3  po_c = vcross(vminus(ray->orig, cy->point), cy->normal);
	t_vec3 cp;

	if (!set_root(
		vlength2(uo_c),
		vdot(uo_c, po_c),
		vlength2(po_c) - cy->radius * cy->radius,
		rec))
		return (FALSE);
	rec->p = ray_at(ray, rec->t);
	cp = vminus(rec->p, cy->point);
	rec->normal = vunit(vminus(cp , vmult_k(cy->normal, vdot(cp, cy->normal))));
	rec->color = cy->color;
	if (fabs(vdot(cp, cy->normal)) > cy->height / 2)
		return (hit_circle(cy, ray, rec));
	set_face_normal(ray, rec);
	//if (fabs(vdot(cp, cy->normal)) < cy->height / 2 + EPSILON
	//	&& fabs(vdot(cp, cy->normal)) > cy->height / 2 - EPSILON )
	//	hit_circle(cy,ray,rec);

	return (TRUE);
}
// 평면상의 한점 (원의 중점 좌표)
//cy->center = vplus(cy->point, vmult_k(cy->normal, cy->height / 2));

// t_bool	hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
// {
// 	t_plane	*pl;
// 	double denominator;
// 	double numerator;
// 	double root;

// 	pl = pl_obj->element;
// 	denominator = vdot(pl->normal, ray->dir);
// 	if (fabs(denominator) < EPSILON)
// 		return (FALSE);
// 	numerator = vdot(vminus(pl->center, ray->orig), pl->normal);
// 	root = numerator / denominator;

// 	// tmin:0과 tmax:INFF 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
// 	if (root < rec->tmin || rec->tmax < root)
// 		return (FALSE);
// 	rec->t = root;
// 	rec->p = ray_at(ray, root);
// 	rec->color = pl->color;
// 	rec->normal = pl->normal;
// 	set_face_normal(ray, rec);
// 	return (TRUE);
// }

t_bool	hit_circle(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	// t_cylinder	*cy;
	double denominator;
	double numerator;
	double root;
	const t_point3	center = vplus(cy->point, vmult_k(cy->normal, cy->height / 2));

	// cy = cy_obj->element;
	denominator = vdot(cy->normal, ray->dir);
	if (fabs(denominator) < EPSILON)
		return (FALSE);
	numerator = vdot(vminus(center, ray->orig), cy->normal);
	root = numerator / denominator;

	// tmin:0과 tmax:INFF 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
	if (root < rec->tmin || rec->tmax < root)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->color = cy->color;
	rec->normal = cy->normal;

	if (vlength(vminus(rec->p, center)) - cy->radius > EPSILON)
		return (FALSE);
	set_face_normal(ray, rec);
	return (TRUE);
}

// t_bool	hit_circle(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
// {
// 	// t_cylinder	*cy;
// 	double denominator;
// 	double numerator;
// 	double root;
// 	const t_point3	center = vplus(cy->point, vmult_k(cy->normal, cy->height / 2));
// 	t_vec3	cp = vminus(rec->p, cy->point);
// 	t_vec3	c_center = vminus(cy->point, center);


// 	if (sqrt(vlength2(cp) - vlength2(c_center)) > cy->radius)
// 		return (FALSE);
// 	// cy = cy_obj->element;
// 	denominator = vdot(cy->normal, ray->dir);
// 	if (fabs(denominator) < EPSILON)
// 		return (FALSE);
// 	numerator = vdot(vminus(center, ray->orig), cy->normal);
// 	root = numerator / denominator;

// 	// tmin:0과 tmax:INFF 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
// 	if (root < rec->tmin || rec->tmax < root)
// 		return (FALSE);
// 	rec->t = root;
// 	rec->p = ray_at(ray, root);
// 	rec->color = cy->color;
// 	rec->normal = cy->normal;
// 	set_face_normal(ray, rec);
// 	return (TRUE);
// }

