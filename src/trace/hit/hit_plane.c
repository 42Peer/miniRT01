/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:04:13 by mher              #+#    #+#             */
/*   Updated: 2022/11/10 17:26:52 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/structures.h"
#include "../../../include/utils.h"
#include "../../../include/trace.h"
#include <math.h>

t_bool      hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
	t_plane	*pl;
	double denom;
	double t;
	double root;

	pl = pl_obj->element;
	denom = vdot(pl->normal, ray->dir);
	if (fabs(denom) < EPSILON)
		return (FALSE);
	t = vdot(vminus(pl->center, ray->orig), pl->normal);
	root = t / denom;

	// tmin:0과 tmax:INFF 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
	if (root < rec->tmin || rec->tmax < root) 
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->albedo = pl_obj->albedo;
	rec->normal = pl->normal;
	set_face_normal(ray, rec);
	return (TRUE);
}
