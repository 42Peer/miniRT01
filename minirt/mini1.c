/*
step 1
RGB color
(255 0 0)       red
(0 255 0)       green
(0 0 255)       blue
(255 255 0)     yellow
(255 255 255)   white
(0 0 0)         black
[0, 1] mapping -> vector, color, physics, albedo
*/
#include "mini.h"
#include "print.h"

int main(void)
{
    int i, j;
    double u, v;
    t_color3 pixel_color;
    t_canvas canv;
    t_camera cam;
    t_ray ray;
    t_sphere sp;

    canv = canvas(400, 300);
    cam = camera(&canv, point3(0, 0, 0));
    sp = sphere(point3(0, 0, -5), 2);

    // P3 색상값이 아스키 코드
    printf("P3\n%d %d\n255\n", canv.width, canv.height);
    j = canv.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < canv.width)
        {
            u = (double)i / (canv.width - 1);     //r
            v = (double)j / (canv.height - 1);    //g
            ray = ray_primary(&cam, u, v);
            pixel_color = ray_color(&ray, &sp);                               //b
            write_color(pixel_color);
            i++;
        }
        j--;
    }
    return 0;
}