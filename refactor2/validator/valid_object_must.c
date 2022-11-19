#include "../include/minirt.h"

void	check_fov(char *str)
{
	double	fov;

	check_double(str, DOUBLE_CHAR);
	fov = a_to_d(str);
	if (fov < 0 || fov > 180)
		exit_with_error("fov must be 0 <= fov <= 180\n");
}

void	check_object_A(char *str)
{
	char	**column;

	column = ft_split(str, ' ');
	check_object_position(&str[1]);
	check_column_cnt(column, 3);
	check_double(column[1], DOUBLE_CHAR);
	check_color3(column[2], COLOR_CHAR);
	check_cnt_A();
	free_split(column);
}

void	check_object_C(char *str)
{
	char	**column;

	column = ft_split(str, ' ');
	check_object_position(&str[1]);
	check_column_cnt(column, 4);
	check_vec3(column[1]);
	check_vec3(column[2]);
	if (vlength(str_to_vec3(column[2])) == 0)
		exit_with_error("invalid vector\n");
	check_fov(column[3]);
	check_cnt_C();
	free_split(column);
}

void	check_object_L(char *str)
{
	char	**column;

	column = ft_split(str, ' ');
	check_object_position(&str[1]);
	check_column_cnt(column, 3);
	check_vec3(column[1]);
	check_double(column[2], DOUBLE_CHAR);
	check_cnt_L();
	free_split(column);
}