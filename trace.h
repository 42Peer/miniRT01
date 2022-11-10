#ifndef TRACE_H
#define TRACE_H

#include "structures.h"
#include "utils.h"

// ray 생성자(정규화 된 ray)
t_ray ray(t_point3 orig, t_vec3 dir);

// ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진 점.
t_point3 ray_at(t_ray *ray, double t);


// primary_ray 생성자
t_ray ray_primary(t_camera *cam, double u, double v);

//광선이 최종적으로 얻게된 픽셀의 색상 값을 리턴.
t_color3    ray_color(t_scene *scene);

 // trace/hit/
t_bool      hit(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool      hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool      hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec);
t_bool          hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec);

void        set_face_normal(t_ray *r, t_hit_record *rec);

t_hit_record record_init(void);

t_color3    phong_lighting(t_scene *scene);
t_light     *light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio);
t_color3    point_light_get(t_scene *scene, t_light *light);
t_vec3      reflect(t_vec3 v, t_vec3 n);

t_bool          in_shadow(t_object *objs, t_ray light_ray, double light_len);



#endif
