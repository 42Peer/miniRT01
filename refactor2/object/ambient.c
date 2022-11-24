/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:39:55 by jujeon            #+#    #+#             */
/*   Updated: 2022/11/24 15:39:55 by jujeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	ambient(t_scene *scene, char **data)
{
	t_ambient	ambient;

	ambient.ambient = a_to_d(data[1]);
	ambient.color = parse_color(data[2]);
	scene->ambient = ambient;
}
