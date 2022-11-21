#include "../include/minirt.h"

int	mlx_esc_exit(int keycode, t_mlx *mlx)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	mlx_exit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(EXIT_SUCCESS);
	return (0);
}

void	set_mlx(t_mlx *mlx)
{
	mlx->width = MLX_WIDTH;
	mlx->height = MLX_HEIGHT;
	mlx->canvas_ratio = MLX_RATIO;
	mlx->mlx = mlx_init();
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "miniRT");
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
		&mlx->line_length, &mlx->endian);
	mlx_key_hook(mlx->win, mlx_esc_exit, mlx);
	mlx_hook(mlx->win, X_EVENT_KEY_EXIT, 0, &mlx_exit, mlx);
}

void	my_mlx_pixel_put(t_mlx *data, int x, int y, t_color3 color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = (int)(color.x * 255) << 16
		| (int)(color.y * 255) << 8 
		| (int)(color.z * 255);
}

static void f()
{
	;
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
			if (i == 400 && j == 300)
				f();
			u = (double)i / (scene->mlx.width - 1);
			v = (double)j / (scene->mlx.height - 1);
			scene->ray = ray_primary(&(scene->camera), u, v);
			pixel_color = ray_color(scene);
			my_mlx_pixel_put(&(scene->mlx), i, j, pixel_color);
			++i;
		}
		++j;
	}
}
