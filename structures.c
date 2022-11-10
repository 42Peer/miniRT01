#include "structures.h"
#include "utils.h"
#include "trace.h"

t_object    *object(t_object_type type, void *element, t_color3 albedo)
{
    t_object    *new;

    if (!(new = (t_object *)malloc(sizeof(t_object))))
        return (NULL);
    new->type = type;
    new->element = element;
    new->albedo = albedo;
    new->next = NULL;
    return (new);
}

t_sphere    *sphere(t_point3 center, double radius)
{
    t_sphere *sp;

    if(!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
        return (NULL);
    sp->center = center;
    sp->radius = radius;
    sp->radius2 = radius * radius;
    return (sp);
}

t_light     *light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio)
{
    t_light *light;

    if(!(light = (t_light *)malloc(sizeof(t_light))))
        return (NULL);
    light->origin = light_origin;
    light->light_color = light_color;
    light->bright_ratio = bright_ratio;
    return (light);
}

t_plane    *plane(t_point3 center, t_vec3 n)
{
    t_plane *p;

    if(!(p = (t_plane *)malloc(sizeof(t_plane))))
        return (NULL);
    p->center = center;
    p->n = n;
    return (p);
}

t_cylinder    *cylinder(t_point3 center, t_point3 n,double radius, double h)
{
    t_cylinder *cy;

    if(!(cy = (t_cylinder *)malloc(sizeof(t_cylinder))))
        return (NULL);
    cy->center = center;
    cy->n = n;
    cy->h = h;
    cy->r = radius;
    cy->r2 = radius * radius;
    return (cy);
}
