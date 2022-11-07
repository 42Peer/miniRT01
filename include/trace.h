/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:05:18 by mher              #+#    #+#             */
/*   Updated: 2022/11/07 16:02:46 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
#define TRACE_H

#include "structures.h"
#include "utils.h"

t_ray ray(t_point3 orig, t_vec3 dir);
t_point3 ray_at(t_ray *ray, double t);

t_ray ray_primary(t_camera *cam, double u, double v);
t_color3 ray_color(t_ray *ray, t_sphere *sphere);

t_bool hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec);
void set_face_normal(t_ray *r, t_hit_record *rec);

#endif
