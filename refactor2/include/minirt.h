#ifndef MINIRT_H
#define MINIRT_H

#include "structures.h"
#include "wrap.h"
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
#endif
