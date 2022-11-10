#ifndef SCENE_H
#define SCENE_H

#include "structures.h"
#include "utils.h"

t_canvas canvas(int width, int height);

t_camera camera(t_canvas *canvas, t_point3 orig, t_point3 orient, double theta);


t_object    *object(t_object_type type, void *element, t_color3 albedo);
t_sphere    *sphere(t_point3 center, double radius);
t_plane    *plane(t_point3 center, t_vec3 n);
t_scene     *scene_init(void);
t_cylinder    *cylinder(t_point3 center, t_point3 n,double radius, double h);



#endif
