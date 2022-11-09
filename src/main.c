#include "../include/print.h"
#include "../include/scene.h"
#include "../include/structures.h"
#include "../include/trace.h"
#include "../include/utils.h"
#include "../lib/libmlx/mlx.h"
#include <stdio.h>

void my_mlx_pixel_put(t_mlx_data *data, int x, int y, t_color3 color) {
  char *dst;

  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  *(unsigned int *)dst = (int)(color.x * 255) << 16 |
                         (int)(color.y * 255) << 8 | (int)(color.z * 255);
}

t_scene *scene_init(void) {
  t_scene *scene;
  t_object *world;
  t_object *lights;
  double ka; // 8.4 에서 설명

  // malloc 할당 실패 시, 실습에서는 return NULㄴㄴL로 해두었지만, 적절한 에러
  // 처리가 필요하다.
  if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
    return (NULL);
  scene->canvas = canvas(500, 500);
  scene->camera = camera(&scene->canvas, point3(0, 0, 0));
  world = object(SP, sphere(point3(-2, 0, -5), 2),
                 color3(1, 1, 1)); // world 에 구1 추가
  oadd(&world, object(SP, sphere(point3(2, 0, -5), 2),
                      color3(0, 0.5, 0))); // world 에 구2 추가
  oadd(&world, object(SP, sphere(point3(0, -1000, 0), 998),
                      color3(1, 1, 1))); // world 에 구3 추가
  scene->world = world;
  lights =
      object(LIGHT_POINT, light_point(point3(0, 10, -5), color3(1, 0, 0), 0.7),
             color3(0, 0, 0)); // 더미 albedo
  // oadd(&lights, object(LIGHT_POINT,
  //  light_point(point3(-0, 10, -5), color3(0, 1, 0), 0.7),
  //  color3(0, 0, 0))); // 더미 albedo
  // oadd(&lights,
  //      object(LIGHT_POINT, light_point(point3(0, 5, -5), color3(0, 0, 1),
  //      0.7),
  //             color3(0, 0, 0))); // 더미 albedo
  scene->light = lights;
  ka = 0.2;                                    // 8.4 에서 설명
  scene->ambient = vmult(color3(1, 1, 1), ka); // 8.4 에서 설명
  return (scene);
}

int main(void) {
  t_mlx_data mlx_data;
  int i;
  int j;
  double u;
  double v;
  t_color3 pixel_color;
  t_scene *scene;

  // Scene setting;
  scene = scene_init();
  mlx_data.mlx = mlx_init();
  mlx_data.win = mlx_new_window(mlx_data.mlx, scene->canvas.width,
                                scene->canvas.height, "miniRT");
  mlx_data.img =
      mlx_new_image(mlx_data.mlx, scene->canvas.width, scene->canvas.height);
  mlx_data.addr = mlx_get_data_addr(mlx_data.img, &mlx_data.bits_per_pixel,
                                    &mlx_data.line_length, &mlx_data.endian);
  printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
  j = scene->canvas.height - 1;
  while (j >= 0) {
    i = 0;
    while (i < scene->canvas.width) {
      u = (double)i / (scene->canvas.width - 1);
      v = (double)j / (scene->canvas.height - 1);
      // ray from camera origin to pixel
      scene->ray = ray_primary(&scene->camera, u, v);
      pixel_color = ray_color(scene);
      my_mlx_pixel_put(&mlx_data, i, scene->canvas.height - 1 - j, pixel_color);
      i++;
    }
    j--;
  }
  mlx_put_image_to_window(mlx_data.win, mlx_data.win, mlx_data.img, 0, 0);
  mlx_loop(mlx_data.mlx);
  return (0);

  // 랜더링
  // P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀
  // 수, 마지막은 사용할 색상값 printf("P3\n%d %d\n255\n", canv.width,
  // canv.height); j = canv.height - 1; while (j >= 0)
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
