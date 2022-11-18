#include "../include/minirt.h"

t_color3	phong_lighting(t_scene *scene)
{
	t_color3	light_color;
	t_object	*lights;

	light_color = vmult_k(scene->ambient.color, scene->ambient.ambient);
	lights = scene->light_list;
	while (lights) 
	{
		if(lights->type == LIGHT_POINT)
			light_color = vplus(light_color,
									point_light_get(scene, lights->element));
		lights = lights->next;
	}
	return (vmin(vmult(light_color, scene->rec.color), color3(1, 1, 1)));
}

t_bool	in_shadow(t_scene *scene, t_vec3 light_vec)
{
	t_ray			light_ray;
	double			light_len;

	light_len = vlength(light_vec);
	light_ray = ray(vplus(scene->rec.p,
					vmult_k(scene->rec.normal, EPSILON)), light_vec);
	scene->rec.tmin = 0;
	scene->rec.tmax = light_len;
	if (hit(scene->object_list, &light_ray, &(scene->rec)))
		return (TRUE);
	return (FALSE);
}

t_color3	get_diffuse(t_scene *scene, t_light *light, t_vec3 light_dir)
{
	double	kd;

	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);
	return (vmult_k(light->light_color, kd));
}

t_color3	get_specular(t_scene *scene, t_light *light, t_vec3 light_dir)
{
	double	spec;
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	t_vec3	light_dir_neg;
	t_vec3	rec_normal;

	light_dir_neg = vmult_k(light_dir, -1);
	rec_normal = scene->rec.normal;
	view_dir = vunit(vmult_k(scene->ray.dir, -1));
	reflect_dir = vminus(light_dir_neg,
					vmult_k(rec_normal, vdot(light_dir_neg, rec_normal) * 2));
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), KSN);
	return (vmult_k(vmult_k(light->light_color, KS), spec));
}

t_color3	point_light_get(t_scene *scene, t_light *light)
{
	t_vec3		light_vec;
	t_vec3		light_dir;
	t_color3	diffuse;
	t_color3	specular;
	double		brightness;

	light_vec = vminus(light->origin, scene->rec.p);
	light_dir = vunit(light_vec); 
	if (in_shadow(scene, light_vec))
		return (color3(0,0,0));
	diffuse = get_diffuse(scene, light, light_dir);
	specular = get_specular(scene, light, light_dir);
	brightness = light->bright_ratio * LUMEN;
	return (vmult_k(vplus(diffuse, specular), brightness));
}
