#include "../include/minirt.h"

t_color3	my_mlx_pixel_get(t_xpm *data, int x, int y)
{
	unsigned char	*dst;

	dst = (unsigned char *)(data->addr \
			+ (y * data->line_length \
			+ x * (data->bits_per_pixel / 8)));
	return (vec3(((dst[2]) / 255.999), \
				((dst[1]) / 255.999), \
				((dst[0]) / 255.999)));
}

t_vec3	get_texture_map(t_sphere *sp, t_vec3 p)
{
	t_vec3	normal;
	double	phi;
	double	theta;
	double	u;
	double	v;

	normal = vunit(vminus(p, sp->center));
	phi = atan2(normal.z, normal.x);
	theta = asin(normal.y);
	u = 1 - (phi + M_PI) / (2 * M_PI);
	v = (theta + M_PI / 2) / M_PI;
	return (my_mlx_pixel_get(&sp->texture, u * (sp->texture.img_w), \
			sp->texture.img_h - v * (sp->texture.img_h)));
}

t_vec3	get_bump_map(t_sphere *sp, t_vec3 p)
{
	t_vec3	normal;
	double	phi;
	double	theta;
	double	u;
	double	v;

	normal = vunit(vminus(p, sp->center));
	phi = atan2(normal.z, normal.x);
	theta = asin(normal.y);
	u = 1 - (phi + M_PI) / (2 * M_PI);
	v = (theta + M_PI / 2) / M_PI;
	return (my_mlx_pixel_get(&sp->bump, u * (sp->bump.img_w), \
				sp->bump.img_h - v * (sp->bump.img_h)));
}

t_vec3	get_normal_vector(t_sphere *sp, t_hit_record *rec)
{
	const t_vec3	u = vunit(vcross(vec3(0, 1, EPSILON), rec->normal));
	const t_vec3	v = vunit(vcross(rec->normal, u));
	const t_vec3	n = vunit(vminus(vmult_k(get_bump_map(sp, rec->p), 2), \
									vec3(1, 1, 1)));

	return (vec3(vdot(vec3(u.x, v.x, rec->normal.x), n), \
				vdot(vec3(u.y, v.y, rec->normal.y), n), \
				vdot(vec3(u.z, v.z, rec->normal.z), n)));
}

t_bool	hit_sphere_bump(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp;
	t_vec3		oc;
	double		a;
	double		half_b;
	double		c;

	sp = sp_obj->element;
	oc = vminus(ray->orig, sp->center);
	a = vlength2(ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius_pow_2;
	if (!set_root(a, half_b, c, rec))
		return (FALSE);
	rec->p = ray_at(ray, rec->t);
	rec->normal = vunit(vminus(rec->p, sp->center));
	rec->color = get_texture_map(sp, rec->p);
	rec->normal = get_normal_vector(sp, rec);
	set_face_normal(ray, rec);
	return (TRUE);
}
