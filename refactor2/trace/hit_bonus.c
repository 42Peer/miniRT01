/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:40:36 by jujeon            #+#    #+#             */
/*   Updated: 2022/11/24 15:40:37 by jujeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	t_bool	front_face;

	front_face = vdot(r->dir, rec->normal) < 0;
	if (!front_face)
		rec->normal = vmult_k(rec->normal, -1);
}

t_bool	hit_obj(t_object *object_list, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (object_list->type == SP)
		hit_result = hit_sphere_bump(object_list, ray, rec);
	else if (object_list->type == PL)
		hit_result = hit_checker(object_list, ray, rec);
	else if (object_list->type == CY)
		hit_result = hit_cylinder(object_list, ray, rec);
	else if (object_list->type == CO)
		hit_result = hit_cone(object_list, ray, rec);
	return (hit_result);
}

t_bool	hit(t_object *object_list, t_ray *ray, t_hit_record *rec)
{
	t_bool			hit_anything;
	t_hit_record	temp_rec;

	temp_rec = *rec;
	hit_anything = FALSE;
	while (object_list)
	{
		if (hit_obj(object_list, ray, &temp_rec))
		{
			hit_anything = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		object_list = object_list->next;
	}
	return (hit_anything);
}
