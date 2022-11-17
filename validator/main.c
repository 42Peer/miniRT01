/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 01:44:16 by mher              #+#    #+#             */
/*   Updated: 2022/11/17 18:00:17 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./lib/libft/libft.h"

int check_cnt_A(void)
{
	static int cnt;
	return (cnt++);
}

int check_cnt_C(void)
{
	static int cnt;
	return (cnt++);
}

int check_cnt_L(void)
{
	static int cnt;
	return (cnt++);
}

int check_cnt_sp(void)
{
	static int cnt;
	return (cnt++);
}

int check_cnt_pl(void)
{
	static int cnt;
	return (cnt++);
}

int check_cnt_cy(void)
{
	static int cnt;
	return (cnt++);
}

void split_free(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

double	a_to_d(const char *str)
{
	double	ret;
	double	d;
	int		sign;

	ret = 0;
	sign = 1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		++str;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while ('0' <= *str && *str <= '9')
		ret = ret * 10 + (*str++ - '0');
	if (*str == '.')
		++str;
	d = 0.1;
	while ('0' <= *str && *str <= '9')
	{
		ret += (*(str++) - '0') * d;
		d *= 0.1;
	}
	return (ret * sign);
}

int	get_file_size(char *filename)
{
	int		count;
	int		fd;
	int		read_byte;
	char	buff[1024];

	read_byte = 1;
	count = 0;
	fd = open(filename, O_RDONLY);
	while (read_byte)
	{
		read_byte = read(fd, buff, 1024);
		count += read_byte;
	}
	close(fd);
	return (count);
}

char *get_file(char *filename, int file_size)
{
	char *file;
	int fd;

	file = (char *)malloc(sizeof(char) * (file_size + 1));
	fd = open(filename, O_RDONLY);
	read(fd, file, file_size);
	file[file_size] = '\0';
	return (file);
}

void check_object_position(char *str)
{
	char *valide_char = "0123456789.,- ";
	int v_len = ft_strlen(valide_char);
	int filter[128] = {0};
	int i;

	i = 0;
	while (i < v_len)
	{
		filter[(int)valide_char[i]] = 1;
		i++;
	}
	while (*str)
	{
		if (filter[(int)*str] == 0)
		{
			printf("invalid object posision: %c\n", *str);
			exit(1);
		}
		str++;
	}
}

void check_column_cnt(char **column, int column_cnt)
{
	int cnt;

	cnt = 0;
	while (column[cnt])
		cnt++;
	if (cnt != column_cnt)
	{
		printf("invalid column cnt %d != %d\n", column_cnt, cnt);
		exit(1);
	}
}

void check_double(char *str)
{
	char *valide_char = "0123456789.";
	int v_len = ft_strlen(valide_char);
	int filter[128] = {0};
	int i;

	i = 0;
	while (i < v_len)
	{
		filter[(int)valide_char[i]] += 1;
		i++;
	}
	if (str[0] == '-')
		str++;
	while (*str)
	{
		if (filter[(int)*str] == 0)
		{
			printf("invalid double : %c\n", *str);
			exit(1);
		}
		if (*str == '.')
			filter[(int)*str] -= 1;
		str++;
	}
}

void check_color3(char *str)
{
	char *valide_char = "0123456789,,";
	int v_len = ft_strlen(valide_char);
	int filter[128] = {0};
	char **color3;
	int tmp;
	int i;

	i = 0;
	while (i < v_len)
	{
		filter[(int)valide_char[i]] += 1;
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (filter[(int)str[i]] == 0)
		{
			printf("invalid color3 : %c\n", str[i]);
			exit(1);
		}
		if (str[i] == ',')
			filter[(int)str[i]] -= 1;
		i++;
	}
	color3 = ft_split(str, ',');
	check_column_cnt(color3, 3);
	i = 0;
	while (i < 3)
	{
		tmp = ft_atoi(color3[i]);
		if (tmp < 0 || tmp > 255)
		{
			printf("invalid color : %d\n", tmp);
			exit(1);
		}
		i++;
	}
	split_free(color3);
}

void check_vec3(char *str)
{
	char **vec3;
	int i;

	vec3 = ft_split(str, ',');
	check_column_cnt(vec3, 3);
	i = 0;
	while (i < 3)
	{
		check_double(vec3[i]);
		i++;
	}
	split_free(vec3);
}

void check_fov(char *str)
{
	double fov;

	check_double(str);
	fov = a_to_d(str);
	if (fov < 0 || fov > 180)
	{
		printf("invalid fov : %lf\n", fov);
		exit(1);
	}
}

void check_object_A(char *str)
{
	char **column;
	column = ft_split(str, ' ');

	check_object_position(&str[1]);
	check_column_cnt(column, 3);

	check_double(column[1]); // ambient ratio
	check_color3(column[2]); // ambient color

	check_cnt_A();
	split_free(column);
}

void check_object_C(char *str)
{
	char **column;
	column = ft_split(str, ' ');

	// todo camera 방향벡터 0,0,0 에러처리

	check_object_position(&str[1]);
	check_column_cnt(column, 4);

	check_vec3(column[1]); // camera position
	check_vec3(column[2]); // camera direction
	check_fov(column[3]);  // fov

	check_cnt_C();
	split_free(column);
}

void check_object_L(char *str)
{
	char **column;
	column = ft_split(str, ' ');

	check_object_position(&str[1]);
	check_column_cnt(column, 4);

	check_vec3(column[1]); // light position
	check_double(column[2]); // light ratio
	check_color3(column[3]); // light color
	
	check_cnt_L();
	split_free(column);
}

void check_object_sp(char *str)
{
	char **column;
	column = ft_split(str, ' ');

	check_object_position(&str[2]);
	check_column_cnt(column, 4);

	check_vec3(column[1]); // sphere position
	check_double(column[2]); // sphere diameter
	check_color3(column[3]); // sphere color

	check_cnt_sp();
	split_free(column);
}

void check_object_pl(char *str)
{
	char **column;
	column = ft_split(str, ' ');

	check_object_position(&str[2]);
	check_column_cnt(column, 4);

	check_vec3(column[1]); // plane position
	check_vec3(column[2]); // plane normal
	check_color3(column[3]); // plane color

	check_cnt_pl();
	split_free(column);
}

void check_object_cy(char *str)
{
	char **column;
	column = ft_split(str, ' ');

	check_object_position(&str[2]);
	check_column_cnt(column, 6);

	check_vec3(column[1]); // cylinder position
	check_vec3(column[2]); // cylinder normal
	check_double(column[3]); // cylinder diameter
	check_double(column[4]); // cylinder height
	check_color3(column[5]); // cylinder color

	check_cnt_cy();
	split_free(column);
}

void check_invalid_char(char *str)
{
	char *valide_char = "ACLsplcy0123456789.,- \n";
	int v_len = ft_strlen(valide_char);
	int filter[128] = {0};
	int i;

	i = 0;
	while (i < v_len)
	{
		filter[(int)valide_char[i]] = 1;
		i++;
	}
	while (*str)
	{
		if (filter[(int)*str] == 0)
		{
			printf("invalid char : %c\n", *str);
			exit(1);
		}
		str++;
	}
}

void check_object_count(void)
{
	int result;

	result = 0;
	if (check_cnt_A() != 1)
		result += printf("Error : Ambient count must be 1\n");
	if (check_cnt_C() != 1)
		result += printf("Error : Camera count must be 1\n");
	if (check_cnt_L() < 1)
		result += printf("Error : Light count must be more than 1\n");
	if (check_cnt_sp() < 1)
		result += printf("Error : sphere count must be more than 1\n");
	if (check_cnt_pl() < 1)
		result += printf("Error : plane count must be more than 1\n");
	if (check_cnt_cy() < 1)
		result += printf("Error : cylinder count must be more than 1\n");
	if (result > 0)
		exit(1);
}

void parse_object(char *str)
{
	char **line;
	line = ft_split(str, '\n');
	int i;
	
	i = 0;
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
		{
			printf("invalid object : %s\n", line[i]);
			exit(1);
		}
		i++;
	}
	split_free(line);
}

void validate_rt(char *str)
{
	check_invalid_char(str);
	parse_object(str);
	check_object_count();
	printf("success\n");
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("usage : ./a.out [file]\n");
		return (0);
	}
	int file_size;
	char *file;

	file_size = get_file_size(av[1]);
	file = get_file(av[1], file_size);

	validate_rt(file);
	return (0);
}
