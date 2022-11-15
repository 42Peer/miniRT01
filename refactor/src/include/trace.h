/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:05:18 by mher              #+#    #+#             */
/*   Updated: 2022/11/10 16:10:14 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
#define TRACE_H

#include "./structures.h"
#include "./utils.h"

t_ray ray(t_point3 orig, t_vec3 dir);
t_point3 ray_at(t_ray *ray, double t);

t_ray ray_primary(t_camera *cam, double u, double v);

t_color3 ray_color(t_scene *scene);

void set_face_normal(t_ray *r, t_hit_record *rec);

t_bool hit(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec);
t_bool hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec);

t_color3 phong_lighting(t_scene *scene);
t_color3 point_light_get(t_scene *scene, t_light *light);

t_bool in_shadow(t_object *objs, t_ray light_ray, double light_len);

#endif
