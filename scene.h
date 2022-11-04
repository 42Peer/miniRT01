#ifndef SCENE_H
#define SCENE_H

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

t_sphere sphere(t_point3 center, double radius) {
  t_sphere sp;

  sp.center = center;
  sp.radius = radius;
  sp.radius_sqr = radius * radius;
  return (sp);
}

t_bool hit_sphere(t_sphere *sp, t_ray *ray) {
  t_vec3 oc; //방향벡터로 나타낸 구의 중심.
  // a, b, c는 각각 t에 관한 2차 방정식의 계수
  double a;
  double b;
  double c;
  double discriminant; //판별식

  oc = vminus(ray->orig, sp->center);
  a = vdot(ray->dir, ray->dir);
  b = 2.0 * vdot(oc, ray->dir);
  c = vdot(oc, oc) - sp->radius_sqr;
  // discriminant 는 판별식
  discriminant = b * b - 4 * a * c;

  // 판별식이 0보다 크다면 광선이 구를 hit한 것!
  return (discriminant > 0);
}

#endif
