/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:21:09 by junkpark          #+#    #+#             */
/*   Updated: 2022/11/24 15:21:09 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	light(t_scene *scene, char **data)
{
	t_light	*light;

	light = wrap_malloc(sizeof(t_light));
	light->origin = str_to_vec3(data[1]);
	light->bright_ratio = a_to_d(data[2]);
	light->light_color = vec3(1, 1, 1);
	oadd(&(scene->light_list), object(light, LIGHT_POINT));
}
