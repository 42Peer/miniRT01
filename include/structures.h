/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:55:22 by mher              #+#    #+#             */
/*   Updated: 2022/11/10 17:16:23 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;
typedef struct s_ray t_ray;
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;
typedef struct s_sphere t_sphere;
typedef struct s_mlx_data t_mlx_data;
typedef struct s_hit_record t_hit_record;
typedef struct s_object t_object;
typedef struct s_light t_light;
typedef struct s_scene t_scene;
typedef struct s_plane t_plane;

typedef int t_bool;
#define FALSE 0
#define TRUE 1

typedef int t_object_type;
#define SP 0
#define PL 1
#define LIGHT_POINT 2

#define EPSILON 1e-6 // 0.000001

#define LUMEN 3 // 이 값을 조절하여 장면의 밝기를 조절할 수 있다.

struct s_vec3 {
  double x;
  double y;
  double z;
};

struct s_ray {
  t_point3 orig;
  t_vec3 dir;
};

struct s_camera {
  t_point3 orig;        // 카메라 원점(위치)
  double viewport_h;    // 뷰포트 세로길이
  double viewport_w;    // 뷰포트 가로길이
  t_vec3 horizontal;    // 수평길이 벡터
  t_vec3 vertical;      // 수직길이 벡터
  double focal_len;     // focal length
  t_point3 left_bottom; // 왼쪽 아래 코너점
};

struct s_canvas {
  int width;           // canvas width
  int height;          // canvas height;
  double aspect_ratio; //종횡비
};

struct s_sphere {
  t_point3 center;
  double radius;
  double radius_pow_2;
};

struct s_plane {
  t_point3 center;
  t_vec3 normal;
};

struct s_mlx_data {
  void *mlx;
  void *win;
  void *img;
  char *addr;
  int bits_per_pixel;
  int line_length;
  int endian;
};

struct s_hit_record {
  double t;      // t는 광선의 원점과 교점 사이의 거리.
  t_point3 p;    // p는 교점의 좌표
  t_vec3 normal; // normal은 교점에서의 법선.
  double tmin;   // tmin은 광선의 원점과 교점 사이의 최소거리.
  double tmax;   // tmax는 광선의 원점과 교점 사이의 최대거리.
  t_bool front_face; // front_face는 광선이 교점을 향해 나가는지, 교점을 향해
                     // 들어오는지를 나타낸다.
  t_color3 albedo; // albedo는 물체의 색상을 나타낸다.
};

struct s_object {
  t_object_type type;
  void *element;
  void *next;
  t_color3 albedo;
};

struct s_light {
  t_point3 origin;
  t_color3 light_color;
  double bright_ratio;
};

struct s_scene {
  t_canvas canvas;
  t_camera camera;
  t_object *world;
  t_object *light;
  t_color3 ambient;
  t_ray ray;
  t_hit_record rec;
};

#endif
