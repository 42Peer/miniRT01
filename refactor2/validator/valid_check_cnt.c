/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check_cnt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:41:04 by jujeon            #+#    #+#             */
/*   Updated: 2022/11/24 15:41:04 by jujeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

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
