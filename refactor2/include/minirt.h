#ifndef MINIRT_H
#define MINIRT_H

#include "structures.h"
#include "wrap.h"
#include "vector.h"
#include "libft.h"
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

int			get_file_size(char *filename);

/*
*				parser
*/
t_scene		parse(char *filename);
char		**file_parser(char *filename);
void		object_parser(char **line, t_scene *scene);

/*
*				object_utils
*/
t_vec3		str_to_vec3(char *s);
double		a_to_d(const char *str);
t_color3	parse_color(char *data);

/*
*				object
*/
t_object	*object(void *object, int type);
void		oadd(t_object **list, t_object *new_obj);
void		sphere(t_scene *scene, char **data);
void		plane(t_scene *scene, char **data);
void		cylinder(t_scene *scene, char **data);
void		light(t_scene *scene, char **data);
void		ambient(t_scene *scene, char **data);
void		camera(t_scene *scene, char **data);

/*
*				trace
*/
t_ray		ray_primary(t_camera *cam, double u, double v);
t_color3	ray_color(t_scene *scene);
t_ray		ray(t_point3 orig, t_vec3 dir);
t_point3	ray_at(t_ray *ray, double t);
t_bool		hit(t_object *object_list, t_ray *ray, t_hit_record *rec);
t_bool		hit_obj(t_object *object_list, t_ray *ray, t_hit_record *rec);
void		set_face_normal(t_ray *r, t_hit_record *rec);
t_bool		set_root(double a, double half_b, double c, t_hit_record *rec);
t_bool		hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec);
t_color3	phong_lighting(t_scene *scene);
t_bool		in_shadow(t_scene *scene, t_vec3 light_vec);
t_color3	get_diffuse(t_scene *scene, t_light *light, t_vec3 light_dir);
t_color3	get_specular(t_scene *scene, t_light *light, t_vec3 light_dir);
t_color3	point_light_get(t_scene *scene, t_light *light);

#endif
