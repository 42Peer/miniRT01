/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:15:01 by mher              #+#    #+#             */
/*   Updated: 2022/11/10 15:57:30 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/structures.h"
#include "../../include/scene.h"

t_sphere    *sphere(t_point3 center, double radius)
{
    t_sphere *sp;

    if(!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
        return (NULL);
    sp->center = center;
    sp->radius = radius;
    sp->radius_pow_2 = radius * radius;
    return (sp);
}

t_plane *plane(t_point3 center, t_vec3 normal)
{
	t_plane *pl;

	if(!(pl = (t_plane *)malloc(sizeof(t_plane))))
		return (NULL);
	pl->center = center;
	pl->normal = normal;
	return (pl);
}

t_light     *light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio)
{
    t_light *light;

    if(!(light = (t_light *)malloc(sizeof(t_light))))
        return (NULL);
    light->origin = light_origin;
    light->light_color = light_color;
    light->bright_ratio = bright_ratio;
    return (light);
}

t_object    *object(t_object_type type, void *element, t_color3 albedo)
{
    t_object    *new;

    if (!(new = (t_object *)malloc(sizeof(t_object))))
        return (NULL);
    new->type = type;
    new->element = element;
    new->next = NULL;
    new->albedo = albedo;
    return (new);
}

