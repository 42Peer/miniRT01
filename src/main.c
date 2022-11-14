/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:17:51 by mher              #+#    #+#             */
/*   Updated: 2022/11/10 16:59:53 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../lib/libmlx/mlx.h"
#include "../include/structures.h"
#include "../include/utils.h"
#include "../include/print.h"
#include "../include/scene.h"
#include "../include/trace.h"

void my_mlx_pixel_put(t_mlx_data *data, int x, int y, t_color3 color)
{
  char *dst;

  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  *(unsigned int*)dst = (int)(color.x * 255) << 16 | (int)(color.y * 255) << 8 | (int)(color.z * 255);
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
    scene->canvas = canvas(400, 300);
    scene->camera = camera(&scene->canvas, point3(0, 0, 0));

	// world 에 붉은 구1 추가
    world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0)); 
	// world 에 초록 구2 추가
    oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0))); 
	// world 에 바닥 구3 추가
    oadd(&world, object(SP, sphere(point3(0, -1000, 0), 998), color3(1, 1, 1))); 

	// world 에 파란 평면 추가
	oadd(&world, object(PL, plane(point3(0, 0, -10), vec3(1, 0, 1)), color3(0, 0, 0.5)));
    scene->world = world;

	// lights 에 광원 추가
    lights = object(LIGHT_POINT, light_point(point3(0, 5, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0));
    // oadd(&lights, object(LIGHT_POINT, light_point(point3(100, 20, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)));

    scene->light = lights;
    ka = 0.1; // 8.4 에서 설명
    scene->ambient = vmult(color3(1,1,1), ka); // 8.4 에서 설명
    return (scene);
}

int main(void)
{
	t_mlx_data mlx_data;
	
    int         i;
    int         j;
    double      u;
    double      v;

    t_color3    pixel_color;
    t_scene     *scene;

    scene = scene_init();

	//Render
	mlx_data.mlx = mlx_init();
	mlx_data.win = mlx_new_window(mlx_data.mlx, scene->canvas.width, scene->canvas.height, "miniRT");
	mlx_data.img = mlx_new_image(mlx_data.mlx, scene->canvas.width, scene->canvas.height);
	mlx_data.addr = mlx_get_data_addr(mlx_data.img, &mlx_data.bits_per_pixel, &mlx_data.line_length, &mlx_data.endian);

	j = scene->canvas.height - 1;
 	while (j >= 0)
    {
		i = 0;
        while (i < scene->canvas.width)
        {
            u = (double)i / (scene->canvas.width - 1);
            v = (double)j / (scene->canvas.height - 1);
            //ray from camera origin to pixel
            scene->ray = ray_primary(&scene->camera, u, v);
            pixel_color = ray_color(scene);
			my_mlx_pixel_put(&mlx_data, i, scene->canvas.height - j, pixel_color);
			++i;
		}
		--j;
	}
	mlx_put_image_to_window(mlx_data.mlx, mlx_data.win, mlx_data.img, 0, 0);
	mlx_loop(mlx_data.mlx);
	return (0);
}
