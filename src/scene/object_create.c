/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:15:01 by mher              #+#    #+#             */
/*   Updated: 2022/11/04 16:24:27 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/structures.h"

t_sphere    sphere(t_point3 center, double radius)
{
    t_sphere sp;

    sp.center = center;
    sp.radius = radius;
    sp.radius_pow_2 = radius * radius;
    return (sp);
}
