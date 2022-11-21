#include "./include/minirt.h"
#include "include/structures.h"
#include "include/vector.h"

typedef struct s_cone
{
	t_point3	center;
	t_vec3		o;
	t_color3	color;
	double		theta;
	//double		height;
}	t_cone;

t_bool	hit_cone(t_object *cone_obj, t_ray *ray, t_hit_record *rec)
{
	const t_cone	*cone = cone_obj->element;

	double	cos2 = cos(cone->theta) * cos(cone->theta);
	t_vec3	ce = vminus(ray->orig, cone->center);
	double	dv = vdot(ray->dir, cone->o); 
	double	ce_v = vdot(ce, cone->o);

	double	a = dv * dv - cos2;
	double	half_b = dv * ce_v - vdot(ce, ray->dir) * cos2;
	double	c = ce_v * ce_v - vdot(ce, ce) * cos2;

	if (!set_root(
			a,
			half_b,
			c,
			rec))
		return (FALSE);
	rec->p = ray_at(ray, rec->t);
	double cp_len = vlength(vminus(rec->p, cone->center));
	
	//if (fabs(vdot(cp, cone->o)) > cone->height / 2)
	//	return (hit_circle(cone, ray, rec, TOP)
	//		|| hit_circle(cone, ray, rec, BOTTOM));
	//rec->normal = vunit(vminus(cp, vmult_k(cone->o, vdot(cp, cone->o))));
	rec->normal = vunit(
		vminus(
			rec->p, 
			vplus(
				cone->center, 
				vmult_k(
					cone->o, 
					cp_len * acos(cone->theta)))));
	
	//(void)cp_len;
	//rec->normal = vec3(0,0,1);
	rec->color = cone->color;
	//set_face_normal(ray, rec);
	return (TRUE);
}


int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		exit_with_error("Wrong number of arguments\n");
	scene = parse(argv[1]);

t_cone *cone = malloc(sizeof(t_cone));
cone->center = vec3(0,5,0);
cone->o = vec3(0,1,0);
cone->color = color3(0,1,0);
cone->theta = M_PI / 6;
//cone->height = 10;
t_object *obj = malloc(sizeof(t_object));
obj->next = 0;
obj->type = CO;
obj->element = cone;
oadd(&scene.object_list, obj);

	set_mlx(&scene.mlx);
	pixel_put(&scene);
	mlx_put_image_to_window(scene.mlx.mlx, scene.mlx.win, scene.mlx.img, 0, 0);
	mlx_loop(scene.mlx.mlx);
}
