#ifndef SCENE_H
#define SCENE_H

#include "minirt.h"

void        my_mlx_pixel_put(t_data *data, int x, int y, t_vec3 *color);
t_canvas    canvas(int  width, int height);
t_camera    camera(t_canvas *canvas, t_point3 origin);

#endif