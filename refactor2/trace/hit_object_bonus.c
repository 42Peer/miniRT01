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

t_color3	my_mlx_pixel_get(t_xpm *data, int x, int y)
{
	unsigned char	*dst;

	dst = (unsigned char*)(data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)));
	return (vec3(((dst[2]) / 255.999), \
				((dst[1]) / 255.999), \
				((dst[0])/ 255.999)));
}

// Convert Cartesian coordinate system to spherical coordinate system
t_vec3	get_sphere_texture_color(t_sphere *sp, t_vec3 p)
{
	// double	phi = atan((p.y - sp->center.y) / (p.x - sp->center.x)); // 0~2pi or (-pi ~ pi)
	// double	theta = acos((p.z - sp->center.z) / sp->radius); // 0 ~ pi

// double	phi = atan((p.z - sp->center.z) / (p.y - sp->center.y)); // 0~2pi or (-pi ~ pi)
// double	theta = acos((p.x - sp->center.x) / sp->radius); // 0 ~ pi

	double	theta = atan((p.x - sp->center.x) / (p.y - sp->center.y)); // 0~pi
	double	phi = acos((p.z - sp->center.z) / sp->radius); // (0 ~ 2pi) or (-pi ~ pi)
	
	// if (phi > 2* M_PI || theta > M_PI)
	// 	printf("phi : %lf theta : %lf\n", phi, theta);
	// double	phi_k = fmod(, M_PI);
	// double	theta_k = fmod();
	//const double	u = 1 - (phi + M_PI) / (2 * M_PI);
	//const double	v = (theta + M_PI / 2) / M_PI;
	//const double	u = phi / (2 * M_PI);

	const double	u = theta / M_PI;
 	const double	v = (phi + M_PI) / (2 * M_PI);
	printf("u : %lf v : %lf\n", u, v);
	//const double	v = (theta + M_PI / 2) / M_PI;
	return (my_mlx_pixel_get(&sp->texture, u * (sp->texture.img_w), v * (sp->texture.img_h)));
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
	// rec->color = sp->color;
	rec->color = get_sphere_texture_color(sp, rec->p);
	rec->normal = vunit(vminus(rec->p, sp->center));
	set_face_normal(ray, rec);
	return (TRUE);
}


// t_vec3	mapping(t_data *data, t_hit_record *rec)
// {
// 	const t_vec3	u = vunit(vcross(vec3(0, 1, EPSILON), rec->normal));
// 	const t_vec3	v = vunit(vcross(rec->normal, u));
// 	double			u_k;
// 	double			v_k;

// 	//u_k = fmod(vdot(rec->p, u), data->img_w);
// 	//v_k = fmod(vdot(rec->p, v), data->img_h);
// 	//if (u_k < 0)
// 	//	u_k += data->img_w;
// 	//if (v_k < 0)
// 	//	v_k += data->img_h;
// 	//return (my_mlx_pixel_get(data , u_k, v_k));

// 	u_k = fmod(vdot(rec->p, u), 1);
// 	v_k = fmod(vdot(rec->p, v), 1);
// 	if (u_k < 0)
// 		u_k += 1;
// 	if (v_k < 0)
// 		v_k += 1;
// 	return (my_mlx_pixel_get(data , data->img_w * u_k, data->img_h * v_k));
// }

// t_vec3	bump_mapping(t_vec3 n, t_hit_record *rec)
// {
// 	const t_vec3	u = vunit(vcross(vec3(0, 1, EPSILON), rec->normal));
// 	const t_vec3	v = vunit(vcross(rec->normal, u));
// 	double			u_k;
// 	double			v_k;

// 	//u_k = fmod(vdot(rec->p, u), data->img_w);
// 	//v_k = fmod(vdot(rec->p, v), data->img_h);
// 	//if (u_k < 0)
// 	//	u_k += data->img_w;
// 	//if (v_k < 0)
// 	//	v_k += data->img_h;
// 	//return (my_mlx_pixel_get(data , u_k, v_k));

// 	u_k = fmod(vdot(rec->p, u), 1);
// 	v_k = fmod(vdot(rec->p, v), 1);
// 	if (u_k < 0)
// 		u_k += 1;
// 	if (v_k < 0)
// 		v_k += 1;
// 	return (vec3(vdot(vec3(u.x, v.x, rec->normal.x), n), vdot(vec3(u.y, v.y, rec->normal.y), n), vdot(vec3(u.z, v.z, rec->normal.z), n)));
// }

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
	// //t_vec3	n = vunit(vminus(vmult_k(mapping(&pl->bump, rec), 2), vec3(1,1,1)));
	// //rec->normal = vunit(bump_mapping(n, rec));
	// rec->color = mapping(&pl->texture, rec);
	set_face_normal(ray, rec);
	return (TRUE);
}
