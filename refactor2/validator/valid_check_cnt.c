#include "../include/minirt.h"

int	check_cnt_ambient(void)
{
	static int	cnt;

	return (cnt++);
}

int	check_cnt_camera(void)
{
	static int	cnt;

	return (cnt++);
}

int	check_cnt_light(void)
{
	static int	cnt;

	return (cnt++);
}
