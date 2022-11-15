/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:20:23 by mher              #+#    #+#             */
/*   Updated: 2022/11/10 16:50:05 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/structures.h"
#include "../../../include/utils.h"
#include "../../../include/trace.h"

t_bool hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere *sp;

    t_vec3  oc; //방향벡터로 나타낸 구의 중심, oc = origin - center
    //a, b, c는 각각 t에 관한 2차 방정식의 계수
    double  a; // D dot D
			   //
    //double  b; // 2 * (D dot (O - C))
	double  half_b;

    double  c; // (O - C) dot (O - C) - R^2
    double  discriminant; //판별식
	double  sqrtd;
	double  root;

    sp = sp_obj->element;
    oc = vminus(ray->orig, sp->center);

	a = vlength2(ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius_pow_2;

	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);

	//두 실근(t) 중 tmin:0과 tmax:INFF 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
    rec->albedo = sp_obj->albedo;
	rec->normal = vunit(vminus(rec->p, sp->center));

	set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장.
	return (TRUE);
}
