#include "../../../include/structures.h"
#include "../../../include/trace.h"
#include "../../../include/utils.h"

// cylinder with height

t_bool hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec) {
  //   t_cylinder *cy;

  //   double a;
  //   double half_b;
  //   double c;
  //   t_vec3 u;
  //   t_vec3 o;
  //   t_vec3 delta_P;
  //   double r;

  //   double discriminant; // 판별식
  //   double sqrtd;
  //   double root;
  //   double hit_height;

  //   cy = cy_obj->element;
  //   u = ray->dir;
  //   o = cy->axis;
  //   r = cy->radius;
  //   delta_P = vminus(ray->origin, cy->center);
  //   a = vlength2(vcross(u, o));
  //   half_b = vdot(vcross(u, o), vcross(delta_P, o));
  //   c = vlength2(vcross(delta_P, o)) - pow(r, 2);
  //   discriminant = half_b * half_b - a * c;
  //   if (discriminant < 0)
  //     return (FALSE);
  //   // 이 시점에서 판별식이 참이 나왔기에 근이 존재한다고 판단한다.
  //   sqrtd = sqrt(discriminant);
  //   root = (-half_b - sqrtd) / a; // 근의 공식 해, 작은 근부터 고려.
  //   if (root < rec->tmin || rec->tmax < root) {
  //     root = (-half_b + sqrtd) / a;
  //     if (root < rec->tmin || rec->tmax < root)
  //       return (FALSE);
  //   }
  //   if (!(hit_height = cy_boundary(cy, ray_at(ray, root))))
  //     return (FALSE);

  //   rec->t = root; // 광선의 원점과 교점까지의 거리를 rec에 저장한다.
  //   rec->p = ray_at(ray, root); // 교점의 좌표를 rec에 저장한다.
  //   rec->normal = get_cylinder_normal(
  //       cy, rec->p, hit_height); // vmult(ray->dir, root)하면 안돼!!!
  //   set_face_normal(ray, rec);
  //   rec->albedo = cy_obj->albedo;
  return (TRUE);
}
