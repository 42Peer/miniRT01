#include <stdio.h>
#include "mlx/mlx.h"
#include "structures.h"
#include "utils.h"
#include "print.h"
#include "scene.h"
#include "trace.h"

typedef struct s_data
{
    void *mlx;
    void *win;
    void *img;
    void *addr;
    int line_length;
    int bits_per_pixel;
    int endian;
}   t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color3 color)
{
	char *dst;

	dst = data->addr + (y *data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = (int)(color.x * 255.999) << 16 | (int)(color.y*255.999) << 8 | (int)(color.z*255.999);
}

t_scene *scene_init(void)
{
    t_scene     *scene;
    t_object    *world;
    t_object    *lights;
    double      ka;

    if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
        return (NULL);
    scene->canvas = canvas(400, 300);
    scene->camera = camera(&scene->canvas, point3(0,0,0));
    world = object(SP, sphere(point3(-2, 0, -5),2), color3(0.5, 0, 0));
    oadd(&world, object(SP, sphere(point3(0,-1000,0), 995), color3(1,1,1)));
    oadd(&world, object(SP, sphere(point3(2,0,-5), 2), color3(0,0.5,0)));
    scene->world = world;
    // 광원 추가                                광원 위치           색상            밝기        반사율(광원 자체의 색상은 부여하지 않은 상태)
    lights = object(LIGHT_POINT, light_point(point3(0,20,0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); // 더미 albedo
    scene->light = lights;
    ka = 0.1;
    scene->ambient = vmult(color3(1,1,1), ka);
    return (scene);
}

int main(void)
{
	int    		i;
    int			j;
    double      u;
    double      v;
	t_color3	pixel_color;
    t_scene     *scene;
    t_data      data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 400, 300, "miniRT");
    data.img = mlx_new_image(data.mlx, 400, 300);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

 //   printf("P3\n%d %d\n255\n", canv.width, canv.height);
    scene = scene_init();
    j = scene->canvas.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < scene->canvas.width)
        {
			u = (double)i / (scene->canvas.width - 1);
			v = (double)j / (scene->canvas.height - 1);
            // 카메라에서 픽셀로 가는 ray
			scene->ray = ray_primary(&scene->camera, u, v);
            pixel_color = ray_color(scene);
            my_mlx_pixel_put(&data, i, scene->canvas.height - j, pixel_color);
			// write_color(pixel_color);
        	++i;
        }
    	--j;
    }
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0,0);
    mlx_loop(data.mlx);

    return (0);
}