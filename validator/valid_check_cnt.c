/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check_cnt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:19:59 by junkpark          #+#    #+#             */
/*   Updated: 2022/11/24 15:19:59 by junkpark         ###   ########.fr       */
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
