#include "../include/minirt.h"

void	check_object_sp(char *str)
{
	char	**column;

	column = ft_split(str, ' ');
	check_object_position(&str[2]);
	check_column_cnt(column, 4);
	check_vec3(column[1]);
	check_double(column[2], DOUBLE_CHAR);
	check_color3(column[3], COLOR_CHAR);
	free_split(column);
}

void	check_object_pl(char *str)
{
	char	**column;

	column = ft_split(str, ' ');
	check_object_position(&str[2]);
	check_column_cnt(column, 4);
	check_vec3(column[1]);
	check_vec3(column[2]);
	check_color3(column[3], COLOR_CHAR);
	free_split(column);
}

void	check_object_cy(char *str)
{
	char	**column;

	column = ft_split(str, ' ');
	check_object_position(&str[2]);
	check_column_cnt(column, 6);
	check_vec3(column[1]);
	check_vec3(column[2]);
	check_double(column[3], DOUBLE_CHAR);
	check_double(column[4], DOUBLE_CHAR);
	check_color3(column[5], COLOR_CHAR);
	free_split(column);
}
