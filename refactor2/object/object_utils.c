#include "../include/minirt.h"

// static void check_valid(char *data)
// {
// 	// 소숫점, 부호, 숫자 아닌거 판단

// 	// -> exit
// }

t_vec3	str_to_vec3(char *data)
{
	t_vec3	vec;
	char	**raw_data;

	
	// , 개수 체크 후 예외처리
	raw_data = ft_split(data, ',');
	// raw_data 3개가 되었는지 체크 필요.
	vec.x = a_to_d(raw_data[0]);
	vec.y = a_to_d(raw_data[1]);
	vec.z = a_to_d(raw_data[2]);
	// 프리해줘야함
	return (vec);
}

t_color3	parse_color(char *data)
{
	t_color3	vec;
	char	**raw_data;

	// , 개수 체크 후 예외처리
	raw_data = ft_split(data, ',');
	// raw_data 3개가 되었는지 체크 필요.
	// 0~255 범위 넘는지 체크
	vec.x = a_to_d(raw_data[0]);
	vec.y = a_to_d(raw_data[1]);
	vec.z = a_to_d(raw_data[2]);
	// 프리해줘야함
	return (vec);
}

double	a_to_d(const char *str)
{
	double	ret;
	double	d;

	ret = 0;
	if (!str)
	{
		printf("a_to_d : str is null\n");
		return (0);
	}
	if (!*str)
	{
		printf("a_to_d : *str is null\n");
		return (0);
	}
	while (*str == ' ' || (9 <= *str && *str <= 13))
		++str;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			ret *= -1;
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
	return (ret);
}

// #include <stdio.h>

// int main(void)
// {
// 	printf("%10lf\n", ft_atod("-0.123"));
// 	printf("%.16lf\n", ft_atod("1.5676423432462123"));
// 	printf("%.16lf\n", ft_atod("-1091283.111111111"));
// 	printf("%lf\n", ft_atod("4.187"));
// }
