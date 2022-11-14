
#include "./include/structures.h"
#include "./lib/libmlx/mlx.h"
#include "./include/utils.h"

void set_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->img = mlx_new_image(&mlx->mlx, mlx->width, mlx->height);
	mlx->win = mlx_new_window(&mlx->mlx, mlx->width, mlx->height, "miniRT");
	mlx->addr = mlx_get_data_addr(&mlx->img, &mlx->bits_per_pixel, &mlx->width, &mlx->endian);
}

void set_scene(t_scene *scene)
{
	set_mlx(&scene->mlx)
}

t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.orig = cam->orig;
	// left_bottom + u * horizontal + v * vertical - origin 의 단위 벡터.
	ray.dir = vunit(vminus(vplus(vplus(cam->left_top, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
	return (ray);
}

void	pixel_put(t_scene *scene)
{
	t_color3	pixel_color;
	int			i;
	int			j;
	double		u;
	double		v;

	j = 0;
 	while (j < scene->mlx.height)
	{
		i = 0;
		while (i < scene->mlx.width)
		{
			u = (double)i / (scene->mlx.width - 1);
			v = (double)j / (scene->mlx.height - 1);
			//scene->ray = ray_primary(&scene->camera, u, v);
			//pixel_color = ray_color(scene);
			//my_mlx_pixel_put(&mlx_data, i, scene->canvas.height - j, pixel_color);
			++i;
		}
		++j;
	}
}

int main(int ac, char **av)
{
	t_scene scene;
	
	if (ac != 2)
		return (1);
	set_scene(&scene);
	pixel_put(&scene);
	

	return (0);

}