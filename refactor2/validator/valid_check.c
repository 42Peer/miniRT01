#include "../include/minirt.h"

void	check_object_position(char *str)
{
	const char	*valid_char = "0123456789.,- ";
	int		filter[128];

	set_filter(filter, valid_char);
	while (*str)
	{
		if (filter[(int)*str] == 0)
			exit_with_error("invalid .rt format\n");
		str++;
	}
}

void	check_column_cnt(char **column, int column_cnt)
{
	int	cnt;

	cnt = 0;
	while (column[cnt])
		cnt++;
	if (cnt != column_cnt)
		exit_with_error("invalid .rt format\n");
}


void	check_double(char *str, char *valid_char)
{
	int		filter[128];

	set_filter(filter, valid_char);
	if (str[0] == '-')
		str++;
	while (*str)
	{
		if (filter[(int)*str] == 0)
			exit_with_error("invalid double format\n");
		if (*str == '.')
			filter[(int)*str] -= 1;
		str++;
	}
}

void	check_color3(char *str, char *valid_char)
{
	int		filter[128];
	char	**color3;
	int		tmp;
	int		i;

	set_filter(filter, valid_char);
	i = 0;
	while (str[i])
	{
		if (filter[(int)str[i]] == 0)
			exit_with_error("invalid color format\n");
		if (str[i] == ',')
			filter[(int)str[i]] -= 1;
		i++;
	}
	color3 = ft_split(str, ',');
	check_column_cnt(color3, 3);
	i = -1;
	while (++i < 3)
	{
		tmp = ft_atoi(color3[i]);
		if (tmp < 0 || tmp > 255)
			exit_with_error("invalid color format\n");
	}
	free_split(color3);
}

void	check_vec3(char *str)
{
	char	**vec3;
	int		i;

	vec3 = ft_split(str, ',');
	check_column_cnt(vec3, 3);
	i = 0;
	while (i < 3)
	{
		check_double(vec3[i], DOUBLE_CHAR);
		i++;
	}
	free_split(vec3);
}
