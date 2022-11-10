#include "scene.h"
#include "structures.h"
#include "trace.h"
#include "utils.h"
#include <math.h>

// t_vec3	rotation(t_vec3 v, t_vec3 orient)
// {
// 	const double	r = ag.a;
// 	const double	b = ag.b;
// 	const double	a = ag.r;

// 	double x, y, z;
	
// 	x = v.x * (cos(a) * cos(b)) + v.y * (cos(a) * sin(b) * sin(r) \
// 	- sin(a) * cos(r)) + v.z * (cos(a) * sin(b) * cos(r) + sin(a) * sin(r));
// 	y = v.x * (sin(a) * cos(b)) + v.y * (sin(a) * sin(b) * sin(r) \
// 	+ cos(a) * cos(r)) + v.z * (sin(a) * sin(b) * cos(r) - cos(a) * sin(r));
// 	z = v.y * cos(b) * sin(r) - v.x * sin(b) + v.z * cos(b) * cos(r);
// 	return (vec3(x, y, z));
// }

t_canvas canvas(int width, int height) {
	t_canvas canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.aspect_ratio = (double)width / (double)height;
	return (canvas);
}

t_camera camera(t_canvas *canvas, t_point3 orig, t_point3 orient, double theta) {
	t_camera cam;
	double focal_len;

	t_vec3	w = vunit(vmult(orient, -1));
	t_vec3	u = vunit(vcross(vec3(0,1,0), w)); 
	t_vec3	v = vcross(w, u);

	cam.orig = orig;
	focal_len = 1.0;
	cam.viewport_h = 2.0 * tan(theta / 180 * M_PI);
	cam.viewport_w = cam.viewport_h * canvas->aspect_ratio;
	cam.focal_len = focal_len;
	// cam.horizontal = vec3(cam.viewport_w, 0, 0);
	// cam.vertical = vec3(0, cam.viewport_h, 0);
	cam.horizontal = vmult(u, cam.viewport_w);
	cam.vertical = vmult(v, cam.viewport_h);;
	// 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
	cam.left_bottom = vminus(
	vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)), vdivide(cam.vertical, 2)),w);
								// vec3(0, 0, focal_len));
	// cam.orient = orient;
	return (cam);
}

t_scene *scene_init(void)
{
	t_scene     *scene;
	t_object    *world;
	t_object    *lights;
	double      ka; // 8.4 에서 설명

	// malloc 할당 실패 시, 실습에서는 return NULL로 해두었지만, 적절한 에러 처리가 필요하다.
	if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
			return (NULL);
	scene->canvas = canvas(800, 600);
	scene->camera = camera(&scene->canvas, point3(5, 5, 0), vunit(point3(-2, -2, -1)), 50);
	world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0)); 
	oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0))); 
	// oadd(&world, object(SP, sphere(point3(0, -1000, -5), 998), color3(1, 1, 1))); 
	oadd(&world, object(PL, plane(point3(0, -2, 0), point3(0, 1, 0)), color3(0.0, 0.2, 0.2))); 
	oadd(&world, object(PL, plane(point3(0, 0, -10), point3(1, 0, 1)), color3(0.2, 0.2, 0))); 
	oadd(&world, object(CY, cylinder(point3(0, 3, -7), point3(0, 1, 0), 1, 1), color3(0.2, 0, 0.2))); 
	scene->world = world;
	lights = object(LIGHT_POINT, light_point(point3(-5, 5, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0));
	oadd(&lights, object(LIGHT_POINT, light_point(point3(5, 5, 0), color3(1, 1, 1), 0.8), color3(0, 0, 0)));
	scene->light = lights;
	ka = 0.1; // 8.4 에서 설명
	scene->ambient = vmult(color3(1,1,1), ka); // 8.4 에서 설명
	return (scene);
}
