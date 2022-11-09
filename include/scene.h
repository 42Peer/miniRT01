/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:08:04 by mher              #+#    #+#             */
/*   Updated: 2022/11/04 14:15:48 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
#define SCENE_H

#include "structures.h"
#include "utils.h"

t_canvas canvas(int width, int height);
t_camera camera(t_canvas *canvas, t_point3 origin);
t_sphere sphere(t_point3 center, double radius);

#endif
