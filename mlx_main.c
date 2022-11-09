#include <stdio.h>
#include "./structures.h"
#include "./utils.h"
#include "print.h"
#include "scene.h"
#include "trace.h"
#include "mlx/mlx.h"
#include <math.h>

typedef struct s_mlx
{
    void    *mlx;
	void	*mlx_win;
	void	*img;
	void	*addr;
     int	bits_per_pixel;
     int	size_line;
     int	endian;
}   t_mlx;


void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, t_color3 pixel_color)
{
	char *dst;
	int offset = (y * mlx->size_line + x * (mlx->bits_per_pixel / 8));
    int color = (int)(pixel_color.x * 255) << 16 | (int)(pixel_color.y * 255) << 8
                | (int)(pixel_color.z * 255);

	dst = mlx->addr	+ offset;
	*(unsigned int*)dst = color;
}

t_scene *scene_init(void)
{
    t_scene     *scene;
    t_object    *world;
    t_object    *lights;
    double      ka;

    if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
    return (NULL);
    scene->canvas = canvas(400, 300);
    scene->camera = camera(&scene->canvas, point3(0, 0, 0));
    world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0));
    oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0,0.5,0)));
    oadd(&world, object(SP, sphere(point3(0, -1000, 0), 999), color3(1, 1, 1)));
    scene->world = world;
    lights = object(LIGHT_POINT, light_point(point3(0, 5, 0), color3(1, 1, 1), 0.5), color3(0,0,0));
    scene->light = lights;
    ka = 0.1;
    scene->ambient = vmult(color3(1, 1, 1), ka);
    return (scene);
}

int	main(void)
{
    int     i;
    int     j;
    double  u;
    double  v;
    double  r;
    double  g;
    double  b;
    t_color3    pixel_color;
    t_canvas    canv;
    t_camera    cam;
    t_ray       ray;
    t_object    *world;
    t_mlx       mlx;
    t_scene     *scene;

    mlx.mlx = mlx_init();
    mlx.mlx_win = mlx_new_window(mlx.mlx, 400, 300, "miniRT");
    mlx.img = mlx_new_image(mlx.mlx, 400, 300);
    mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel,
		&mlx.size_line, &mlx.endian);
    //Scene setting;
    //캔버스의 가로, 세로 픽셀값
    scene = scene_init();

    // 랜더링
    // P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
    printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
    j = 0;
    while (j < scene->canvas.height)
    {
        i = 0;
        while (i < scene->canvas.width)
        {
            u = (double)i / (scene->canvas.width - 1);
            v = (double)(scene->canvas.height - j) / (scene->canvas.height - 1);
            //ray from camera origin to pixel
            ray = ray_primary(&scene->camera, u, v);
            pixel_color = ray_color(scene);
            // write_color(pixel_color);
            my_mlx_pixel_put(&mlx, i, j, pixel_color);
            ++i;
        }
    ++j;
    }
    mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, 0,0);
    mlx_loop(mlx.mlx);
    return (0);
}

// #include "mlx/mlx.h"
// #include <math.h>

// typedef struct  s_data
// {
//   void	*img;
//   char	*addr;
//   int	bits_per_pixel;
//   int	size_line;
//   int	endian;
// }               t_data;

// void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
// {
// 	char *dst;
// 	int offset = (y * img->size_line + x * (img->bits_per_pixel / 8));

// 	dst = img->addr	+ offset;
// 	*(unsigned int*)dst = color;
// }

// int	is_circle(int i, int j, int x, int y)
// {
// 	if (200 >= sqrt(powf(x-i, 2) + powf(y-j,2)))
// 		return (1);
// 	return (0);
// }

// int main()
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	t_data	img;
// 	int 	i,j,k;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 600, 600, "MiniRT");
// 	img.img = mlx_new_image(mlx, 600, 600);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
// 		&img.size_line, &img.endian);
// 	// my_mlx_pixel_put(&img, 150, 150, 0x00FF0000);
// 	// for (i = 250, k = 99; i< 300; i++, k -= 2)
// 	// {
// 	// 	for (j = 150 + k; j < 250; j++)
// 	// 	{
// 	// 		my_mlx_pixel_put(&img, i, j, 0x3cc3ff);
// 	// 	}
// 	// }
// 	// for (i = 300, k = 0; i < 350; i++, k += 2)
// 	// {
// 	// 	for (j = 150 + k; j < 250; j++)
// 	// 		my_mlx_pixel_put(&img, i, j, 0x3cc3ff);
// 	// }
// 	for (int j = 100; j < 500; j++)
// 	{
// 		for (int i = 100; i < 500; i++)
// 		{
// 			if (is_circle(i, j, 300, 300) == 1)
// 				my_mlx_pixel_put(&img, i, j, 0x3cc3ff);
// 		}
// 	}
// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0,0);
// 	mlx_loop(mlx);
// }