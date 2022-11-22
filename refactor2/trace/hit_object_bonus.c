#include "../include/minirt.h"

t_bool	hit_circle_cone(const t_cone *cone, \
					t_ray *ray, t_hit_record *rec)
{
	double		denominator;
	double		numerator;
	double		root;
	t_vec3		normal;
	t_point3	center;

	normal = cone->normal;
	center = vplus(cone->point, vmult_k(normal, cone->height));
	denominator = vdot(normal, ray->dir);
	if (fabs(denominator) < EPSILON)
		return (FALSE);
	numerator = vdot(vminus(center, ray->orig), normal);
	root = numerator / denominator;
	if (root < rec->tmin || rec->tmax < root)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->color = cone->color;
	rec->normal = normal;
	if (vlength(vminus(rec->p, center)) - cone->height * tan(cone->theta) \
		> EPSILON)
		return (FALSE);
	set_face_normal(ray, rec);
	return (TRUE);
}

t_bool	hit_cone(t_object *cone_obj, t_ray *ray, t_hit_record *rec)
{
	const t_cone	*cone = cone_obj->element;
	const t_vec3	ce = vminus(ray->orig, cone->point);
	const double	dv = vdot(ray->dir, cone->normal);
	const double	ce_v = vdot(ce, cone->normal);
	double			cp_len;

	if (!set_root(
			dv * dv - pow(cos(cone->theta), 2),
			dv * ce_v - vdot(ce, ray->dir) * pow(cos(cone->theta), 2),
			ce_v * ce_v - vdot(ce, ce) * pow(cos(cone->theta), 2),
			rec))
		return (FALSE);
	rec->p = ray_at(ray, rec->t);
	cp_len = vlength(vminus(rec->p, cone->point));
	if (vdot(vminus(rec->p, cone->point), cone->normal) < 0)
		return (FALSE);
	if (cp_len * cos(cone->theta) > cone->height)
		return (hit_circle_cone(cone, ray, rec));
	rec->normal = vunit(vminus(rec->p, vplus(cone->point, \
		vmult_k(cone->normal, cp_len * acos(cone->theta)))));
	rec->color = cone->color;
	set_face_normal(ray, rec);
	return (TRUE);
}

t_color3	get_checker_color(t_plane *pl, t_hit_record *rec)
{
	const t_vec3	u = vunit(vcross(vec3(0, 1, EPSILON), rec->normal));
	const t_vec3	v = vunit(vcross(rec->normal, u));
	double			u_k;
	double			v_k;

	u_k = fmod(vdot(rec->p, u), CHECKER_SIZE * 2);
	v_k = fmod(vdot(rec->p, v), CHECKER_SIZE * 2);
	if (u_k < 0)
		u_k += CHECKER_SIZE * 2;
	if (v_k < 0)
		v_k += CHECKER_SIZE * 2;
	if (u_k < CHECKER_SIZE && v_k < CHECKER_SIZE)
		return (pl->color);
	else if (u_k >= CHECKER_SIZE && v_k >= CHECKER_SIZE)
		return (pl->color);
	else
		return (color3(0, 0, 0));
}

t_bool	hit_checker(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
	t_plane	*pl;
	double	denominator;
	double	numerator;
	double	root;

	pl = pl_obj->element;
	denominator = vdot(pl->normal, ray->dir);
	if (fabs(denominator) < EPSILON)
		return (FALSE);
	numerator = vdot(vminus(pl->center, ray->orig), pl->normal);
	root = numerator / denominator;
	if (root < rec->tmin || rec->tmax < root)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = pl->normal;
	rec->color = get_checker_color(pl, rec);
	set_face_normal(ray, rec);
	return (TRUE);
}
