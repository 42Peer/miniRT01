/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:17:51 by mher              #+#    #+#             */
/*   Updated: 2022/11/07 12:42:30 by mher             ###   ########.fr       */
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

int main(void)
{
	t_mlx_data mlx_data;
	
    int         i;
    int         j;
    double      u;
    double      v;

    t_color3    pixel_color;
    t_canvas    canv;
    t_camera    cam;
    t_ray       ray;
    t_sphere    sp;

    //Scene setting;
    canv = canvas(400, 300);
    cam = camera(&canv, point3(0, 0, 0));
	sp = sphere(point3(0, 0, -5), 2);

	//Render
	mlx_data.mlx = mlx_init();
	mlx_data.win = mlx_new_window(mlx_data.mlx, canv.width, canv.height, "miniRT");
	mlx_data.img = mlx_new_image(mlx_data.mlx, canv.width, canv.height);
	mlx_data.addr = mlx_get_data_addr(mlx_data.img, &mlx_data.bits_per_pixel, &mlx_data.line_length, &mlx_data.endian);

	i = canv.height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < canv.width)
		{
			u = (double)j / (canv.width - 1);
			v = (double)i / (canv.height - 1);
			ray = ray_primary(&cam, u, v);
			pixel_color = ray_color(&ray, &sp);
			my_mlx_pixel_put(&mlx_data, j, canv.height - i, pixel_color);
			j++;
		}
		i--;
	}
	mlx_put_image_to_window(mlx_data.mlx, mlx_data.win, mlx_data.img, 0, 0);
	mlx_loop(mlx_data.mlx);
	return (0);


    // 랜더링
    // P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
    // printf("P3\n%d %d\n255\n", canv.width, canv.height);
    // j = canv.height - 1;
    // while (j >= 0)
    // {
    //     i = 0;
    //     while (i < canv.width)
    //     {
    //         u = (double)i / (canv.width - 1);
    //         v = (double)j / (canv.height - 1);
    //         //ray from camera origin to pixel
    //         ray = ray_primary(&cam, u, v);
	// 		pixel_color = ray_color(&ray, &sp);
    //         write_color(pixel_color);
    //         ++i;
    //     }
    //     --j;
    // }
}
