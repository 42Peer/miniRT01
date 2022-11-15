#ifndef MINIRT_H
#define MINIRT_H

#include "structures.h"
#include "wrap.h"
#include "vector.h"
#include "libft.h"
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

int	get_file_size(char *filename);

/*
*				parser
*/
t_scene	parse(char *filename);
char	**file_parser(char *filename);
void	object_parser(char **line, t_scene *scene);

t_vec3	str_to_vec3(char *s);
double	a_to_d(const char *str);
t_color3	parse_color(char *data);
/*
*				object
*/
t_object	*object(void *object, int type);
void        oadd(t_object **list, t_object *new_obj);
void	sphere(t_scene *scene, char **data);
void	plane(t_scene *scene, char **data);
void	cylinder(t_scene *scene, char **data);
void	light(t_scene *scene, char **data);
void	ambient(t_scene *scene, char **data);
void	camera(t_scene *scene, char **data);


#endif
