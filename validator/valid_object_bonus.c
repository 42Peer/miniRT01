/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_object_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:20:04 by junkpark          #+#    #+#             */
/*   Updated: 2022/11/24 15:20:04 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	check_object_co(char *str)
{
	char	**column;

	column = ft_split(str, ' ');
	check_object_position(&str[2]);
	check_column_cnt(column, 6);
	check_vec3(column[1]);
	check_vec3(column[2]);
	check_double(column[3], DOUBLE_CHAR);
	check_theta(column[4]);
	check_color3(column[5], COLOR_CHAR);
	free_split(column);
}
