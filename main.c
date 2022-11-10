#include "print.h"
#include "scene.h"
#include "structures.h"
#include "trace.h"
#include <stdio.h>
#include "mlx/mlx.h"
#include "my_mlx.h"

int main(void) {
	int i;
	int j;
	double u;
	double v;
	// const double aspect_ratio = 16.0 / 9.0;
	t_color3	pixel_color;
	t_scene     *scene;

	// Scene setting;
	scene = scene_init();

	// mlx setting
	t_mlx mlx;
	t_data    img;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, scene->canvas.width, scene->canvas.height, "miniRT");
	img.img = mlx_new_image(mlx.mlx, scene->canvas.width, scene->canvas.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	j = scene->canvas.height - 1;
	/* * * * 수정 끝 * * * */
	while (j >= 0) {
		i = 0;
		while (i < scene->canvas.width) {
			u = (double)i / (scene->canvas.width - 1);
			v = (double)j / (scene->canvas.height - 1);
			//ray from camera origin to pixel
			scene->ray = ray_primary(&scene->camera, u, v);
			pixel_color = ray_color(scene);
			// write_color(pixel_color);
			my_mlx_pixel_put(&img, i, scene->canvas.height - 1 - j, (int)(255.999 * pixel_color.x) << 16 | (int)(255.999 * pixel_color.y) << 8 | (int)(255.999 * pixel_color.z));
			++i;
		}
		--j;
	}

	mlx_key_hook(mlx.win, key_hooking, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_loop(mlx.mlx);
	return (0);
}
