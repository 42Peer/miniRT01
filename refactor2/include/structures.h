#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct s_vec3		t_vec3;
typedef struct s_vec3		t_point3;
typedef struct s_vec3		t_color3;
typedef struct s_ray		t_ray;
typedef struct s_camera		t_camera;
typedef struct s_sphere		t_sphere;
typedef struct s_mlx		t_mlx;
typedef struct s_hit_record	t_hit_record;
typedef struct s_object		t_object;
typedef struct s_light		t_light;
typedef struct s_scene		t_scene;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_ambient	t_ambient;

typedef int t_bool;
#define FALSE 0
#define TRUE 1

typedef enum e_object_type 
{
	SP,
	PL,
	CY,
	LIGHT_POINT,
	AMBIENT,
}	t_object_type;

#define EPSILON 1e-6 // 0.000001
#define LUMEN 3 // 이 값을 조절하여 장면의 밝기를 조절할 수 있다.

#define MLX_WIDTH	800
#define MLX_HEIGHT	600
#define MLX_RATIO	(MLX_WIDTH / MLX_HEIGHT)

#define KS 0.5
#define KSN 64
// 3차원 좌표계
struct s_vec3 
{
	double x;
	double y;
	double z;
};

// 벡터
struct s_ray 
{
	t_point3 orig;	// 시점
	t_vec3 dir;		 // 방향
};

// 카메라 (type == C)
struct s_camera 
{
	t_point3	orig;			// 카메라 원점(위치)
	t_vec3		camera_dir;		// 카메라의 방향벡터(보는 방향)
	double		focal_len;		// focal length
	double		viewport_h;		// 뷰포트 세로길이
	double		viewport_w;		// 뷰포트 가로길이
	t_vec3		horizontal;		// 수평길이 벡터
	t_vec3		vertical;		// 수직길이 벡터
	t_point3	left_top;		// 뷰포트의 왼쪽 상단 ()  origin + viewport_h / 2 - viewport_w / 2	
};

// type == sp
struct s_sphere 
{
	t_point3	center;			// 원의 중심
	double		radius;			// 반지름 = diameter / 2
	double		radius_pow_2;	// 반지름^2
	t_color3	color;			// 색상
};


// type == pl
struct s_plane 
{
	t_point3	center;	// 평면 내의 한 점
	t_vec3		normal;	// 평면의 법선 벡터
	t_color3	color;	// 색상
};

// type == cy
struct s_cylinder
{
	t_point3	point;	// todo: 원기둥의 한 점? 근데 어디 한점?????????
	t_vec3		normal; // 법선벡터
	t_color3	color;	// RGB
	double		radius; // 밑면의 반지름 = diameter / 2
	double		height; // 원기둥의 높이
};

// type == A
struct s_ambient
{
	double		ambient;	// 주변광의 밝기
	t_color3	color;		// 주변광의 RGB
};

// canvas 구조체로 변경

struct s_hit_record
{
	double		t;			// t는 광선(ray, light_ray)의 원점과 교점 사이의 거리.
	t_point3	p;			// p는 교점의 좌표
	t_vec3		normal;		// normal은 교점에서의 법선.
	double		tmin;		// tmin은 광선의 원점과 교점 사이의 최소거리.
	double		tmax;		// tmax는 광선의 원점과 교점 사이의 최대거리.
	t_color3	color;		// albedo는 물체의 색상을 나타낸다.
};

struct s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
};

// type == L
struct s_light
{
	t_point3	origin;			// 광원의 위치
	t_color3	light_color;	// 광원의 색상 => 보너스 영역에서만 사용
	double		bright_ratio;	// 밝기
};

struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		width;				// line_length
	int		height;
	int		line_length;
	double	canvas_ratio;
};

struct s_scene
{
	t_mlx			mlx;
	t_camera		camera;
	t_object		*object_list;
	t_object		*light_list;
	t_ambient 		ambient;
	t_ray			ray;			// camera -> viewport
	t_hit_record	rec;			// ray가 만난 교점(hit)의 정보
};

#endif
