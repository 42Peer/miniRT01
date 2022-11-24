/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:40:09 by jujeon            #+#    #+#             */
/*   Updated: 2022/11/24 15:40:09 by jujeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	cone(t_scene *scene, char **data)
{
	t_cone	*cone;

	cone = wrap_malloc(sizeof(t_cone));
	cone->point = str_to_vec3(data[1]);
	cone->normal = vunit(str_to_vec3(data[2]));
	cone->theta = a_to_d(data[3]) * M_PI / 180;
	cone->height = a_to_d(data[4]);
	cone->color = parse_color(data[5]);
	oadd(&scene->object_list, object(cone, CO));
}
