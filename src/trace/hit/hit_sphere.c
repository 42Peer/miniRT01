/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:20:23 by mher              #+#    #+#             */
/*   Updated: 2022/11/04 17:01:41 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/structures.h"
#include "../../../include/utils.h"

t_bool      hit_sphere(t_sphere *sp, t_ray *ray)
{
    t_vec3  oc; //방향벡터로 나타낸 구의 중심, oc = origin - center
    //a, b, c는 각각 t에 관한 2차 방정식의 계수
    double  a; // D dot D
    double  b; // 2 * (D dot (O - C))
    double  c; // (O - C) dot (O - C) - R^2
    double  discriminant; //판별식

    oc = vminus(ray->orig, sp->center);
    a = vdot(ray->dir, ray->dir);
    b = 2.0 * vdot(oc, ray->dir);
    c = vdot(oc, oc) - sp->radius_pow_2;
    // discriminant 는 판별식
    discriminant = b * b - 4 * a * c;

    // 판별식이 0보다 크다면 광선이 구를 hit한 것!
    return (discriminant > 0);
}
