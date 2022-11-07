#ifndef TRACE_H
#define TRACE_H

#include "scene.h"
#include "structures.h"
#include "utils.h"
#include <math.h>

// ray 생성자(정규화 된 ray)
t_ray ray(t_point3 orig, t_vec3 dir) {
  t_ray ray;

  ray.orig = orig;
  ray.dir = vunit(dir);
  return (ray);
}

// ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진 점.
t_point3 ray_at(t_ray *ray, double t) {
  t_point3 at;

  at = vplus(ray->orig, vmult(ray->dir, t));
  return (at);
}

// primary_ray 생성자
t_ray ray_primary(t_camera *cam, double u, double v) {
  t_ray ray;

  ray.orig = cam->orig;
  // left_bottom + u * horizontal + v * vertical - origin 의 단위 벡터.
  ray.dir =
      vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)),
                         vmult(cam->vertical, v)),
                   cam->orig));
  return (ray);
}

//광선이 최종적으로 얻게된 픽셀의 색상 값을 리턴.
t_color3 ray_color(t_ray *ray, t_object *world) {
  double t;
  // t_vec3 n;
  t_hit_record rec;

  rec.tmin = 0;
  rec.tmax = INFINITY;
  if (hit(world, ray, &rec))
    return (vmult(vplus(rec.normal, color3(1, 1, 1)), 0.5));
  else {
    // ray의 방향벡터의 y 값을 기준으로 그라데이션을 주기 위한 계수.
    t = 0.5 * (ray->dir.y + 1.0);
    // (1-t) * 흰색 + t * 하늘색
    return (vplus(vmult(color3(1, 1, 1), 1.0 - t),
                  vmult(color3(0.5, 0.7, 1.0), t)));
  }
}

void set_face_normal(t_ray *r, t_hit_record *rec) {
  // 광선의 방향벡터와 교점의 법선벡터의 내적이 음수이면 광선은 앞면(객체의)에
  // hit 한 것이다
  rec->front_face = vdot(r->dir, rec->normal) < 0;
  // 광선의 앞면에 hit 면 그대로 아니면 법선을 반대로 뒤집는다. (항상 광선
  // 방향벡터와 법선 벡터를 반대인 상태로 사용하기위해)
  rec->normal = (rec->front_face) ? rec->normal : vmult(rec->normal, -1);
}

#endif
