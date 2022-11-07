#ifndef STRUCTURES_H
#define STRUCTURES_H

// 1. 벡터 구조체
typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;

// 2. 트레이스 구조체
typedef struct s_ray t_ray;
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;

// 3. 오브젝트 구조체
typedef struct s_object t_object;
typedef struct s_sphere t_sphere;

// 4. 식별자
typedef int t_bool;
#define FALSE 0
#define TRUE 1
typedef enum e_object_type {
  SP,
} t_object_type;

// 5. hit_record
typedef struct s_hit_record t_hit_record;

// 1. 벡터 구조체
struct s_vec3 {
  double x;
  double y;
  double z;
};

// 2. 트레이스 구조체
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

// 3. 오브젝트 구조체
struct s_object {
  t_object_type type;
  void *element;
  t_object *next;
};

struct s_sphere {
  t_point3 center;
  double radius;
  double radius_sqr;
};

// 5. hit_record
struct s_hit_record {
  t_point3 p;
  t_vec3 normal;
  double tmin;
  double tmax;
  double t;
  t_bool front_face;
};

#endif
