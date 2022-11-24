/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:21:05 by junkpark          #+#    #+#             */
/*   Updated: 2022/11/24 15:21:05 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	cylinder(t_scene *scene, char **data)
{
	t_cylinder	*cylinder;

	cylinder = wrap_malloc(sizeof(t_cylinder));
	cylinder->point = str_to_vec3(data[1]);
	cylinder->normal = vunit(str_to_vec3(data[2]));
	cylinder->radius = a_to_d(data[3]) / 2;
	cylinder->height = a_to_d(data[4]);
	cylinder->color = parse_color(data[5]);
	oadd(&scene->object_list, object(cylinder, CY));
}
