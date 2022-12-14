/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:08:04 by mher              #+#    #+#             */
/*   Updated: 2022/11/10 16:01:52 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
#define SCENE_H

#include "structures.h"
#include "utils.h"

t_canvas canvas(int width, int height);
t_camera camera(t_canvas *canvas, t_point3 origin);
t_object *object(t_object_type type, void *element, t_color3 albedo);
t_sphere *sphere(t_point3 center, double radius);
t_plane *plane(t_point3 center, t_vec3 normal);
t_light *light_point(t_point3 light_origin, t_color3 light_color,
                     double bright_ratio);

#endif
