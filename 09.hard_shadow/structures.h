#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_vec3		t_vec3;
typedef struct s_vec3		t_point3;
typedef struct s_vec3		t_color3;
typedef struct s_ray		t_ray;
typedef struct s_camera		t_camera;
typedef struct s_canvas		t_canvas;
typedef struct s_sphere		t_sphere;
typedef struct s_light		t_light;
typedef struct s_object		t_object;
typedef struct s_scene		t_scene;
typedef struct s_hit_record	t_hit_record;

typedef int				t_bool;
# define FALSE 0
# define TRUE 1
typedef int				t_object_type;
# define SP 0
# define LIGHT_POINT 1
# define EPSILON 1e-6
# define LUMEN 3

struct s_vec3
{
	double x;
	double y;
	double z;
};

// 카메라 -> 오브젝트
struct s_ray
{
	t_point3	orig;			// ray의 origin
	t_vec3 		dir;
};

struct s_camera
{
	t_point3	orig;			// 카메라 원점(위치) - (0,0,0)
	double		viewport_h;		// 뷰포트 세로
	double		viewport_w;		// 뷰포트 가로
	t_vec3		horizontal;		// 수평길이 벡터
	t_vec3		vertical;		// 수직길이 벡터
	double		focal_len;		// focal length
	t_point3	left_bottom;	// 왼쪽 아래 코너점
};

struct s_canvas
{
	int		width;			// 캔버스 가로
	int		height;			// 캔버스 세로
	double	aspect_ratio;	// 종횡비(가로세로 비율)
};

struct s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
};

struct s_hit_record
{
	t_point3	p;				// 교점의 좌표
	t_vec3		normal;			// 교점에서의 법선
	double		tmin;			// 0 : t가 음수이면 오브젝트가 카메라 뒤에 있다는 말, 즉 보이지 않는 상황
	double		tmax;			// INFINITY : 너무 멀어도 안보임
	double		t;				// 광선의 원점과 교점 사이의 거리
	t_bool		front_face;
	t_color3	albedo;			// 반사율
};

struct s_object
{
	t_object_type	type;		// 오브젝트의 종류
	void			*element;	// sphere
	void			*next;
	t_color3		albedo;		// 반사율
};

struct s_light
{
	t_point3	origin;
	t_color3	light_color;
	double		bright_ratio;
};

struct s_scene
{
	t_canvas		canvas;
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_color3		ambient;
	t_ray			ray;
	t_hit_record	rec;
};



#endif