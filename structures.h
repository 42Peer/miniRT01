#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;
typedef struct s_ray t_ray;
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;
typedef struct s_sphere t_sphere;
typedef struct s_hit_record t_hit_record;
typedef struct s_object t_object;
typedef struct s_light t_light;
typedef struct s_scene t_scene;


struct s_vec3 {
	double x;
	double y;
	double z;
};

typedef int             t_bool;
# define FALSE 0
# define TRUE 1

# define EPSILON 1e-6 // 0.000001
# define LUMEN 2

typedef int             t_object_type;
# define SP 0
# define LIGHT_POINT 1
# define PL 2
# define CY 3


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
	// t_vec3	orient;
};

struct s_canvas {
	int width;           // canvas width
	int height;          // canvas height;
	double aspect_ratio; //종횡비
};

struct  s_sphere
{
		t_point3    center;
		double      radius;
		double      radius2;
};

typedef struct  s_plane
{
		t_point3    center;
		t_vec3      n;
}	t_plane;

typedef struct  s_cylinder
{
		t_point3    center;
		t_vec3      n;
		double		h;
		double		r;
		double		r2;
}	t_cylinder;

struct s_hit_record
{
		t_point3    p;
		t_vec3      normal;
		double      tmin;
		double      tmax;
		double      t;
		t_bool      front_face;
		t_color3    albedo;
};

struct                      s_object
{
		t_object_type   type;
		t_color3    		albedo;
		void            *element;
		void            *next;
};

struct      s_light
{
		t_point3    origin;
		t_color3    light_color;
		double      bright_ratio;
};

struct  s_scene
{
		t_canvas        canvas;
		t_camera        camera;
		t_object        *world;
		t_object        *light;
		t_color3         ambient; // 8.4에서 설명할 요소
		t_ray           ray;
		t_hit_record    rec;
};

#endif
