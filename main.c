#include "minilibx_opengl_20191021/mlx.h"
#include "print.h"
#include "scene.h"
#include "structures.h"
#include "trace.h"
#include <stdio.h>

int main(void) {
  int i;
  int j;
  double u;
  double v;
  t_color3 pixel_color;
  t_canvas canv;
  t_camera cam;
  t_ray ray;
  t_object *world;

  int bits_per_pixel;
  int size_line;
  int endian;
  void *mlx_ptr = mlx_init();
  void *mlx_win = mlx_new_window(mlx_ptr, 400, 300, "miniRT");
  void *img_ptr = mlx_new_image(mlx_ptr, 400, 300);
  void *data_addr =
      mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);

  // Scene setting;
  canv = canvas(400, 300);
  cam = camera(&canv, point3(0, 0, 0));
  world = object(SP, sphere(point3(-2, 0, -5), 2)); // world 에 구1 추가
  oadd(&world, object(SP, sphere(point3(2, 0, -5), 2))); // world 에 구2 추가
  oadd(&world,
       object(SP, sphere(point3(0, -1000, 0), 990))); // world 에 구3 추가

  // 랜더링
  // P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀
  // 수, 마지막은 사용할 색상값
  /* * * * 수정 * * * */
  printf("P3\n%d %d\n255\n", canv.width, canv.height);
  j = 0;
  /* * * * 수정 끝 * * * */
  while (j < canv.height) {
    i = 0;
    /* * * * 수정 * * * */
    while (i < canv.width) {
      u = (double)i / (canv.width - 1);
      v = (double)j / (canv.height - 1);
      // ray from camera origin to pixel
      ray = ray_primary(&cam, u, v);
      pixel_color = ray_color(&ray, world);
      // write_color(pixel_color);
      *(unsigned int *)(data_addr + ((canv.height - j) * size_line +
                                     i * (bits_per_pixel / 8))) =
          (int)(pixel_color.x * 255.999) << 16 |
          (int)(pixel_color.y * 255.999) << 8 | (int)(pixel_color.z * 255.999);
      ++i;
    }
    ++j;
  }
  mlx_put_image_to_window(mlx_ptr, mlx_win, img_ptr, 0, 0);
  mlx_loop(mlx_ptr);
  return (0);
}
