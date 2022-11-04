#ifndef MINI_H
#define MINI_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;

struct s_vec3
{
    double x;
    double y;
    double z;
};

// vector operations
t_vec3      vec3(double x, double y, double z)
{
    t_vec3 vec;

    vec.x = x;
    vec.y = y;
    vec.z = z;
    return (vec);
}
t_point3    point3(double x, double y, double z)
{
    t_vec3 point;

    point.x = x;
    point.y = y;
    point.z = z;
    return (point);
}
t_point3    color3(double r, double g, double b)
{
    t_color3 color;

    color.x = r;
    color.y = g;
    color.z = b;
    return (color);
}
void        vset(t_vec3 *vec, double x, double y, double z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}
double      vlength2(t_vec3 vec)
{
    return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
double      vlength(t_vec3 vec)
{
    return (sqrt(vlength2(vec)));
}
t_vec3      vplus(t_vec3 vec, t_vec3 vec2)
{
    vec.x += vec2.x;
    vec.y += vec2.y;
    vec.z += vec2.z;
    return (vec);
}
t_vec3      vplus_(t_vec3 vec, double x, double y, double z)
{
    vec.x += x;
    vec.y += y;
    vec.z += z;
    return (vec);
}
t_vec3      vminus(t_vec3 vec, t_vec3 vec2)
{
    vec.x -= vec2.x;
    vec.y -= vec2.y;
    vec.z -= vec2.z;
    return (vec);
}
t_vec3      vminus_(t_vec3 vec, double x, double y, double z)
{
    vec.x -= x;
    vec.y -= y;
    vec.z -= z;
    return (vec);
}
t_vec3      vmult(t_vec3 vec, double t)
{
    vec.x *= t;
    vec.y *= t;
    vec.z *= t;
    return (vec);
}
t_vec3      vmult_(t_vec3 vec, t_vec3 vec2)
{
    vec.x *= vec2.x;
    vec.y *= vec2.y;
    vec.z *= vec2.z;
    return (vec);
}
t_vec3      vdivide(t_vec3 vec, double t)
{
    vec.x *= 1 / t;
    vec.y *= 1 / t;
    vec.z *= 1 / t;
    return (vec);
}
double      vdot(t_vec3 vec, t_vec3 vec2) // 벡터 내적
{
    return (vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z);
}
t_vec3      vcross(t_vec3 vec, t_vec3 vec2) // 벡터 외적
{
    t_vec3 new_vec;

    new_vec.x = vec.y * vec2.z - vec.z * vec2.y;
    new_vec.y = vec.z * vec2.x - vec.x * vec2.z;
    new_vec.z = vec.x * vec2.y - vec.y * vec2.x;
    return (new_vec);
}
t_vec3      vunit(t_vec3 vec) // 단위 벡터
{
    double len = vlength(vec);
    if (len == 0)
    {
        printf("Error\n:Devider is 0");
        exit(0);
    }
    vec.x /= len;
    vec.y /= len;
    vec.z /= len;
    return (vec);
}
t_vec3      vmin(t_vec3 vec1, t_vec3 vec2) // 두 벡터의 원소를 비교하여 작은 값들만 반환
{
    if (vec1.x > vec2.x)
        vec1.x = vec2.x;
    if (vec1.y > vec2.y)
        vec1.y = vec2.y;
    if (vec1.z > vec2.z)
        vec1.z = vec2.z;
    return (vec1);
}

// ray
typedef struct s_ray t_ray;

struct s_ray
{
    t_point3 orig;
    t_vec3   dir;
};
// 정규화된 ray 생성
t_ray   ray(t_point3 orig, t_vec3 dir)
{
    t_ray ray;

    ray.orig = orig;
    ray.dir = vunit(dir);
    return (ray);
}
// ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진 점
t_point3 ray_at(t_ray *ray, double t)
{
    t_point3 at;

    at = vplus(ray->orig, vmult(ray->dir, t));
    return (at);
}

// camera
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;

struct s_camera
{
    t_point3 orig; // 카메라 원점(위치)
    double   viewport_h; // 뷰포트 세로길이
    double   viewport_w; // 뷰포트 가로길이
    t_vec3   horizontal; // 수평길이 벡터
    t_vec3   vertical; // 수직길이 벡터
    double   focal_len; // focal length
    t_point3 left_bottom; // 맨쪽 아래 코너점
};
struct s_canvas
{
    int width;
    int height;
    double aspect_ratio; // 종횡비
};

t_canvas canvas(int width, int height)
{
    t_canvas canvas;

    canvas.width = width;
    canvas.height = height;
    canvas.aspect_ratio = (double)width / (double)height;
    return (canvas);
}
t_camera camera(t_canvas *canvas, t_point3 orig)
{
    t_camera cam;
    double   focal_len;
    double   viewport_height;

    viewport_height = 2.0;
    focal_len = 1.0;
    cam.orig = orig;
    cam.viewport_h = viewport_height;
    cam.viewport_w = viewport_height * canvas->aspect_ratio;
    cam.focal_len = focal_len;
    cam.horizontal = vec3(cam.viewport_w, 0, 0);
    cam.vertical = vec3(0, cam.viewport_h, 0);
    //왼쪽 아래 코너점 좌표, origin -horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length)
    cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)), vdivide(cam.vertical, 2)), vec3(0, 0, focal_len));
    return (cam);
}

t_ray ray_primary(t_camera *cam, double u, double v)
{
    t_ray ray;

    ray.orig = cam->orig;
    //left_bottom + u * horizontal + v * vertical - origin의 단위 벡터
    ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
    return (ray);
}

// sphere
typedef struct s_sphere t_sphere;

typedef int t_bool;
#define FALSE 0
#define TRUE 1

struct s_sphere
{
    t_point3 center;
    double radius;
    double radius2;
};

t_bool hit_sphere(t_sphere *sp, t_ray *ray)
{
    t_vec3 oc;

    double a;
    double b;
    double c;
    double discriminant; // 판별식

    oc = vminus(ray->orig, sp->center);
    a = vdot(ray->dir, ray ->dir);
    b = 2.0 * vdot(oc, ray->dir);
    c = vdot(oc, oc) - sp->radius2;

    discriminant = b * b - 4 * a * c;

    return (discriminant > 0);
}

t_color3 ray_color(t_ray *r, t_sphere *sphere)
{
    double t;

    if (hit_sphere(sphere, r))
        return (color3(1, 0, 0));
    else
    {
        t = 0.5 * (r->dir.y + 1.0);
        // (1-t) * 흰색 + t * 하늘색
        return (vplus(vmult(color3(1,1,1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t)));
    }
}

t_sphere sphere(t_point3 center, double radius)
{
    t_sphere sp;

    sp.center = center;
    sp.radius = radius;
    sp.radius2 = radius * radius;
    return (sp);
}

#endif