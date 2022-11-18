/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnam <jnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 01:44:16 by mher              #+#    #+#             */
/*   Updated: 2022/11/18 16:25:04 by jnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	check_cnt_A(void)
{
	static int	cnt;

	return (cnt++);
}

int	check_cnt_C(void)
{
	static int	cnt;

	return (cnt++);
}

int	check_cnt_L(void)
{
	static int	cnt;

	return (cnt++);
}

void	check_object_position(char *str)
{
	char	*valid_char = "0123456789.,- ";
	int		v_len = ft_strlen(valid_char);
	int		filter[128] = {0};
	int		i;

	i = 0;
	while (i < v_len)
	{
		filter[(int)valid_char[i]] = 1;
		i++;
	}
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

void	set_filter(int *filter, char* valid_char)
{
	const int	v_len = ft_strlen(valid_char);
	int			i;

	i = 0;
	while (i < 128)
	{
		filter[i] = 0;
		i++;
	}
	i = 0;
	while (i < v_len)
	{
		filter[(int)valid_char[i]] += 1;
		i++;
	}
}

void	check_double(char *str, char *valid_char)
{
	int		v_len = ft_strlen(valid_char);
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

void	check_invalid_char(char *str, char *valid_char)
{
	int		filter[128];

	set_filter(filter, valid_char);
	while (*str)
	{
		if (filter[(int)*str] == 0)
			exit_with_error("invalid .rt format\n");
		str++;
	}
}

void	parse_object(char *str)
{
	char	**line;
	int		i;
	
	i = 0;
	line = ft_split(str, '\n');
	while (line[i])
	{
		if (line[i][0] == 'A')
			check_object_A(line[i]);
		else if (line[i][0] == 'C')
			check_object_C(line[i]);
		else if (line[i][0] == 'L')
			check_object_L(line[i]);
		else if (line[i][0] == 's' && line[i][1] == 'p')
			check_object_sp(line[i]);
		else if (line[i][0] == 'p' && line[i][1] == 'l')
			check_object_pl(line[i]);
		else if (line[i][0] == 'c' && line[i][1] == 'y')
			check_object_cy(line[i]);
		else
			exit_with_error("invalid object\n");
		i++;
	}
	free_split(line);
}

void	validate_rt(char *str)
{
	check_invalid_char(str, VALID_CHAR);
	parse_object(str);
	if (check_cnt_A() != 1 || check_cnt_C() != 1 || check_cnt_L() != 1)
		exit_with_error("invalid object count\n");
}