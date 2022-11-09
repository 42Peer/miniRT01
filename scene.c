#include "scene.h"
#include "structures.h"
#include "utils.h"

t_canvas canvas(int width, int height) {
  t_canvas canvas;

  canvas.width = width;
  canvas.height = height;
  canvas.aspect_ratio = (double)width / (double)height;
  return (canvas);
}

t_camera camera(t_canvas *canvas, t_point3 orig) {
  t_camera cam;
  double focal_len;
  double viewport_height;

  viewport_height = 2.0;
  focal_len = 1.0;
  cam.orig = orig;
  cam.viewport_h = viewport_height;
  cam.viewport_w = viewport_height * canvas->aspect_ratio;
  cam.focal_len = focal_len;
  cam.horizontal = vec3(cam.viewport_w, 0, 0);
  cam.vertical = vec3(0, cam.viewport_h, 0);
  // 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 -
  // vec3(0,0,focal_length)
  cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)),
                                  vdivide(cam.vertical, 2)),
                           vec3(0, 0, focal_len));
  return (cam);
}

t_object *object(t_object_type type, void *element) {
  t_object *_new;

  if (!(_new = (t_object *)malloc(sizeof(t_object))))
    return (NULL);
  _new->type = type;
  _new->element = element;
  _new->next = NULL;
  return (_new);
}

t_sphere *sphere(t_point3 center, double radius) {
  t_sphere *sp;

  if (!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
    return (NULL);
  sp->center = center;
  sp->radius = radius;
  sp->radius_sqr = radius * radius;
  return (sp);
}

// t_sphere sphere(t_point3 center, double radius) {
//   t_sphere sp;

//   sp.center = center;
//   sp.radius = radius;
//   sp.radius_sqr = radius * radius;
//   return (sp);
// }

t_bool hit_obj(t_object *world, t_ray *ray, t_hit_record *rec) {
  t_bool hit_result;

  hit_result = FALSE;
  if (world->type == SP)
    hit_result =
        hit_sphere(world, ray, rec); // hit_sphere의 첫번째 인자도 t_sphere
                                     // *에서 t_object *로 수정해주자.
  return (hit_result);
}

t_bool hit(t_object *world, t_ray *ray, t_hit_record *rec) {
  t_bool hit_anything;
  t_hit_record temp_rec;

  temp_rec = *rec; // temp_rec의 tmin, tmax 값 초기화를 위해.
  hit_anything = FALSE;
  while (world) {
    if (hit_obj(world, ray, &temp_rec)) {
      hit_anything = TRUE;
      temp_rec.tmax = temp_rec.t;
      *rec = temp_rec;
    }
    world = world->next;
  }
  return (hit_anything);
}

t_bool hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec) {
  t_sphere *sp = (t_sphere *)world->element;
  t_vec3 oc; //방향벡터로 나타낸 구의 중심.
  // a, b, c는 각각 t에 관한 2차 방정식의 계수
  double a;
  double half_b;
  double c;
  double discriminant; //판별식
  double sqrtd;
  double root;

  oc = vminus(ray->orig, sp->center);
  // a = vdot(ray->dir, ray->dir);
  // b = 2.0 * vdot(oc, ray->dir);
  // c = vdot(oc, oc) - sp->radius_sqr;
  // // discriminant 는 판별식
  // discriminant = b * b - 4 * a * c;

  // if (discriminant < 0) // 판별식이 0보다 작을 때 : 실근 없을 때,
  //   return (-1.0);
  // else
  //   return ((-b - sqrt(discriminant)) / (2.0 * a)); // 두 근 중 작은 근
  a = vlength2(ray->dir);
  half_b = vdot(oc, ray->dir);
  c = vlength2(oc) - sp->radius_sqr;
  discriminant = half_b * half_b - a * c;

  if (discriminant < 0)
    return (FALSE);
  sqrtd = sqrt(discriminant);
  root = (-half_b - sqrtd) / a;
  root = (-half_b - sqrtd) / a;
  if (root < rec->tmin || rec->tmax < root) {
    root = (-half_b + sqrtd) / a;
    if (root < rec->tmin || rec->tmax < root)
      return (FALSE);
  }
  rec->t = root;
  rec->p = ray_at(ray, root);
  rec->normal =
      vdivide(vminus(rec->p, sp->center), sp->radius); // 정규화된 법선 벡터.
  set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서
                             // 앞면인지 뒷면인지 t_bool 값으로 저장.
  return (TRUE);
}
