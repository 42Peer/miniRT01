#include "../../include/scene.h"
#include "../../include/structures.h"

t_object *object(t_object_type type, void *element, t_color3 albedo) {
  t_object *new;

  if (!(new = (t_object *)malloc(sizeof(t_object))))
    return (NULL);
  new->type = type;
  new->element = element;
  new->next = NULL;
  new->albedo = albedo;
  return (new);
}

t_sphere *sphere(t_point3 center, double radius) {
  t_sphere *sp;

  if (!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
    return (NULL);
  sp->center = center;
  sp->radius = radius;
  sp->radius_pow_2 = radius * radius;
  return (sp);
}

t_light *light_point(t_point3 orig, t_color3 color, double brightness) {
  t_light *light;

  if (!(light = (t_light *)malloc(sizeof(t_light))))
    return (NULL);
  light->orig = orig;
  light->color = color;
  light->brightness = brightness;
  return (light);
}
