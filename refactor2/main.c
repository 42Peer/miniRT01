#include "./include/minirt.h"

#include "./include/structures.h"
#include "./lib/libmlx/mlx.h"
// #include "./include/utils.h"

void set_mlx(t_mlx *mlx)
{
	mlx->width = MLX_WIDTH;
	mlx->height = MLX_HEIGHT;
	mlx->canvas_ratio = MLX_RATIO;
	mlx->mlx = mlx_init();
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "miniRT");
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
}

void my_mlx_pixel_put(t_mlx *data, int x, int y, t_color3 color)
{
  char *dst;

  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  *(unsigned int*)dst = (int)(color.x * 255) << 16 | (int)(color.y * 255) << 8 | (int)(color.z * 255);
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
			scene->ray = ray_primary(&(scene->camera), u, v);
			pixel_color = ray_color(scene);
			my_mlx_pixel_put(&(scene->mlx), i, j, pixel_color);
			++i;
		}
		++j;
	}
}

int main(int argc, char **argv)
{
	t_scene	scene;
	// mini.rt 파일인지 확장자 검사 필요
	if (argc != 2)
		return (1);
	scene = parse(argv[1]);
	set_mlx(&scene.mlx);
	pixel_put(&scene);
	mlx_put_image_to_window(scene.mlx.mlx, scene.mlx.win, scene.mlx.img, 0, 0);
	mlx_loop(scene.mlx.mlx);
	// printf_test(&scene);
}

/*
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
*/