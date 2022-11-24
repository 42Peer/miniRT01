/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:40:49 by jujeon            #+#    #+#             */
/*   Updated: 2022/11/24 15:40:49 by jujeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_color3	phong_lighting(t_scene *scene)
{
	t_color3	light_color;
	t_object	*lights;

	light_color = vmult_k(scene->ambient.color, scene->ambient.ambient);
	lights = scene->light_list;
	while (lights)
	{
		if (lights->type == LIGHT_POINT)
			light_color = vplus(light_color, \
									point_light_get(scene, lights->element));
		lights = lights->next;
	}
	return (vmin(vmult(light_color, scene->rec.color), color3(1, 1, 1)));
}

t_bool	in_shadow(t_scene *scene, t_vec3 light_vec)
{
	t_ray			light_ray;
	double			light_len;
	t_hit_record	tmp_rec;

	light_len = vlength(light_vec);
	light_ray = ray(vplus(scene->rec.p, \
					vmult_k(scene->rec.normal, EPSILON)), light_vec);
	tmp_rec.tmin = 0;
	tmp_rec.tmax = light_len;
	if (hit(scene->object_list, &light_ray, &tmp_rec))
		return (TRUE);
	return (FALSE);
}

t_color3	get_diffuse(t_scene *scene, t_light *light, t_vec3 light_dir)
{
	double	kd;

	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);
	return (vmult_k(light->light_color, kd));
}

t_color3	point_light_get(t_scene *scene, t_light *light)
{
	t_vec3		light_vec;
	t_vec3		light_dir;
	t_color3	diffuse;
	double		brightness;

	light_vec = vminus(light->origin, scene->rec.p);
	light_dir = vunit(light_vec);
	if (in_shadow(scene, light_vec))
		return (color3(0, 0, 0));
	diffuse = get_diffuse(scene, light, light_dir);
	brightness = light->bright_ratio * LUMEN;
	return (vmult_k(diffuse, brightness));
}
