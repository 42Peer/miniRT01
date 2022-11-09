#include "trace.h"

t_vec3		reflect(t_vec3 v, t_vec3 n)
{
	return (vminus(v, vmult(n, vdot(v, n)*2)));
}

t_color3	point_light_get(t_scene *scene, t_light *light)
{
	t_color3	diffuse;
	t_vec3		light_dir;		// 교점->광원 벡터
	double		light_len;
	t_ray		light_ray;		// hit_point로부터 광원으로 가는 벡터
	double		kd;				// diffuse의 강도
	t_color3	specular;
	t_vec3		view_dir;		// 교점->카메라 벡터
	t_vec3		reflect_dir;	// light_dir을 법선 기준으로 대칭시킨 벡터(반사광?)
	double		spec;
	double		ksn;
	double		ks;
	double		brightness;

	// (교점 -> 광원)의 단위벡터
	light_dir = vminus(light->origin, scene->rec.p);
	// hit point로부터 광원의 원점까지의 거리
	light_len = vlength(light_dir);
	light_ray = ray(vplus(scene->rec.p, vmult(scene->rec.normal, EPSILON)), light_dir);
				// 법선백터랑 (교점to광원)벡터를 내적
	if (in_shadow(scene->world, light_ray, light_len))
		return (color3(0,0,0)); // ambient를 어케 처리하지? 
	light_dir = vunit(light_dir);
	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);
	// 빛의 원래 밝기에 kd를 곱해서 현재 좌표가 가져야하는 밝기
	diffuse = vmult(light->light_color, kd);
	view_dir = vunit(vmult(scene->ray.dir, -1));
	reflect_dir = reflect(vmult(light_dir, -1), scene->rec.normal);
	ksn = 64;
	ks = 0.5;
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	specular = vmult(vmult(light->light_color, ks), spec);
	brightness = light->bright_ratio * LUMEN;
	return (vmult(vplus(diffuse, specular), brightness));
}

t_color3	phong_lighting(t_scene *scene)
{
	t_color3	light_color;
	t_object	*lights;

	// 광원이 하나도 없다면, 빛의 양은 0,0,0
	light_color = color3(0,0,0);
	lights = scene->light;
	// 여러 광원에서 나오는 모든 빛에 대해 각각 diffuse, specular값을 모두 구해줘야 함 => bonus
	while (lights)
	{
		if (lights->type == LIGHT_POINT)
			light_color = vplus(light_color, point_light_get(scene, lights->element));
		lights = lights->next;
	}
	light_color = vplus(light_color, scene->ambient);
	return (vmin(vmult_(light_color, scene->rec.albedo), color3(1,1,1)));
	// 모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1,1,1)을 넘으면 (1,1,1)을 반환
}

t_bool	in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_hit_record rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}