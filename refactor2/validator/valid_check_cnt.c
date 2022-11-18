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