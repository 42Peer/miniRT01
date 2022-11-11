#include "minirt.h"

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
    world = object(SP, sphere(point3(-2, 0 , -5), 2), color3(0.5, 0, 0));
    oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0)));
    oadd(&world, object(SP, sphere(point3(0, -1000, 0), 995), color3(1, 1, 1))); // 998
    // oadd(&world, object(SP, ));
    scene->world = world;
    lights = object(LIGHT_POINT, light_point(point3(0, 20, 0), color3(1, 1, 1), 0.5), color3(0, 0,0)); // dummy albedo
    scene->light = lights;
    ka = 0.1;
    scene->ambient = vmult(color3(1,1,1), ka);
    return (scene);
}

int main(void)
{
    int i;
    int j;
    double  u;
    double  v;
    t_color3    pixel_color;
    // t_sphere    sp;
    void        *mlx;
    void        *mlx_win;
    t_data      img;
    t_scene     *scene;

    scene = scene_init();

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 400, 300, "miniRT");
    img.img = mlx_new_image(mlx, 400, 300);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    j = scene->canvas.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < scene->canvas.width)
        {
            u = (double)i / (scene->canvas.width - 1);
            v = (double)j / (scene->canvas.height - 1);
            scene->ray = ray_primary(&scene->camera, u, v);
            pixel_color = ray_color(scene);
            my_mlx_pixel_put(&img, i, scene->canvas.height - j, &pixel_color);
            i++;
        }
        j--;
    }
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
    return (0);
}