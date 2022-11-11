#ifndef OBJECT_H
#define OBJECT_H

#include "minirt.h"

t_sphere    *sphere(t_point3 center, double radius);
t_object    *object(t_object_type type, void *element, t_color3 albedo);
void        oadd(t_object **list, t_object *new);
t_object    *olast(t_object *list);
t_light     *light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio);

#endif