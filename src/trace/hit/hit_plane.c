#include "../../../include/structures.h"
#include "../../../include/trace.h"
#include "../../../include/utils.h"
#include <math.h>

t_bool hit_plane(t_object *obj, t_ray *ray, t_hit_record *rec) {
  t_plane *pl = (t_plane *)obj->element;
  double t;
  double denom;

  denom = vdot(ray->dir, pl->normal);
  printf("dir: %f %f %f ", ray->dir.x, ray->dir.y, ray->dir.z);
  printf("normal: %f %f %f ", pl->normal.x, pl->normal.y, pl->normal.z);
  printf("denom: %f ", denom);
  if (fabs(denom) != 0) {
    t = vdot(vminus(pl->point, ray->orig), pl->normal) / denom;
    printf("t: %f\n", t);
    if (t < rec->tmin || rec->tmax < t)
      return (FALSE);
    rec->t = t;
    rec->p = ray_at(ray, t);
    rec->normal = pl->normal;
    set_face_normal(ray, rec);
    rec->albedo = obj->albedo;
    return (TRUE);
  }
  printf("\n");
  return (FALSE);
}
