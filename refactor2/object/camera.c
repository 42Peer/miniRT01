#include "../include/minirt.h"

// C '-50.0,0,20' '0,0,1' '70' xyz 방향벡터 FOV(dgrees)

void	camera(t_scene *scene, char **data)
{
	t_camera	*camera;
	double		degree;
// 파싱
	camera = wrap_malloc(sizeof(t_camera));
	camera->orig = str_to_vec3(data[1]);
	camera->camera_dir = str_to_vec3(data[2]);
	degree = a_to_d(data[3]);
	camera->focal_len = 1;
	camera->viewport_h = 2 * tan((degree / 2) * (M_PI / 180));
	camera->viewport_w = scene->mlx.canvas_ratio * camera->viewport_h;
	camera->horizontal = vec3(camera->viewport_w, 0, 0);
    camera->vertical = vec3(0, (camera->viewport_h), 0);
	//camera->left_top = vplus(camera->orig, vminus(
	//							vec3(0, camera->viewport_h / 2, 0), cameravec3(->viewport_w / 2, 0, 0)));
	scene->camera = *camera;
	camera->left_top = vminus(vminus(vplus(camera->orig, vdivide_k(camera->horizontal, 2)),
					vdivide_k(camera->vertical, 2)), vec3(0, 0, camera->focal_len));

	//cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)),
    //                            vdivide(cam.vertical, 2)), vec3(0, 0, focal_len));
}
// 파싱 이후 vector 계산

// struct s_camera 
// {
// 	t_point3	orig;			// 카메라 원점(위치)
// 	t_vec3		camera_dir;		// 카메라의 방향벡터(보는 방향)
// 	double		focal_len;		// focal length
// 	double		viewport_h;		// 뷰포트 세로길이
// 	double		viewport_w;		// 뷰포트 가로길이
// 	t_vec3		horizontal;		// 수평길이 벡터
// 	t_vec3		vertical;		// 수직길이 벡터
// 	t_point3	left_top;		// 뷰포트의 왼쪽 상단 ()  origin + viewport_h / 2 - viewport_w / 2	
// };
