#include "../include/minirt.h"

t_vec3	str_to_vec3(char *data)
{
	t_vec3	vec;
	char	**raw_data;

	raw_data = ft_split(data, ',');
	vec.x = a_to_d(raw_data[0]);
	vec.y = a_to_d(raw_data[1]);
	vec.z = a_to_d(raw_data[2]);
	free_split(raw_data);
	return (vec);
}

t_color3	parse_color(char *data)
{
	t_color3	vec;
	char		**raw_data;

	raw_data = ft_split(data, ',');
	vec.x = a_to_d(raw_data[0]) / 255.999;
	vec.y = a_to_d(raw_data[1]) / 255.999;
	vec.z = a_to_d(raw_data[2]) / 255.999;
	free_split(raw_data);
	return (vec);
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

double	minf(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

double	maxf(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
