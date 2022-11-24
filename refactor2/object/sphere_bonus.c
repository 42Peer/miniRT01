/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:40:22 by jujeon            #+#    #+#             */
/*   Updated: 2022/11/24 15:40:23 by jujeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	sphere(t_scene *scene, char **data)
{
	t_sphere	*sphere;

	sphere = wrap_malloc(sizeof(t_sphere));
	sphere->center = str_to_vec3(data[1]);
	sphere->radius = a_to_d(data[2]) / 2;
	sphere->radius_pow_2 = pow(sphere->radius, 2);
	sphere->color = parse_color(data[3]);
	sphere->texture.img = mlx_xpm_file_to_image(scene->mlx.mlx, \
		"./asset/gold_ball_texture.xpm", &sphere->texture.img_w, \
		&sphere->texture.img_h);
	if (sphere->texture.img == NULL)
		exit_with_error("unvalid xpm file\n");
	sphere->texture.addr = (unsigned char *)mlx_get_data_addr(\
	sphere->texture.img, &sphere->texture.bits_per_pixel, \
	&sphere->texture.line_length, &sphere->texture.endian);
	sphere->bump.img = mlx_xpm_file_to_image(scene->mlx.mlx, \
		"./asset/gold_ball_bump.xpm", &sphere->bump.img_w, &sphere->bump.img_h);
	if (sphere->bump.img == NULL)
		exit_with_error("unvalid xpm file\n");
	sphere->bump.addr = (unsigned char *)mlx_get_data_addr(sphere->bump.img, \
	&sphere->bump.bits_per_pixel, \
	&sphere->bump.line_length, &sphere->bump.endian);
	oadd(&(scene->object_list), object(sphere, SP));
}
