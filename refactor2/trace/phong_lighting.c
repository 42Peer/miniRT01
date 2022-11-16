#include "../include/minirt.h"

t_color3        phong_lighting(t_scene *scene)
{
    t_color3    light_color;
    t_object    *lights;

	// ambient 는 한번만 적용하기 때문에 초기화할때 한번만 해주면 된다.
    light_color = vmult_k(scene->ambient.color, scene->ambient.ambient);
    lights = scene->light_list;
	//여러 광원에서 나오는 모든 빛에 대해 각각 diffuse, specular 값을 모두 구해줘야 한다
    while (lights) 
    {
        if(lights->type == LIGHT_POINT) 
            light_color = vplus(light_color, point_light_get(scene, lights->element));
        lights = lights->next;
    }
    //모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 
	//그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.
    return (vmin(vmult(light_color, scene->rec.color), color3(1, 1, 1)));
}


t_bool	in_shadow(t_scene *scene, t_vec3 light_vec)
{
	t_ray	light_ray; 
	double	light_len; 

	light_len = vlength(light_vec); 
	light_ray = ray(vplus(scene->rec.p, vmult_k(scene->rec.normal, EPSILON)), light_vec); 
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
