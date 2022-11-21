/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 01:44:16 by mher              #+#    #+#             */
/*   Updated: 2022/11/21 20:24:05 by jujeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

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
	char			**line;
	static int		i;

	line = ft_split(str, '\n');
	while (line[i])
	{
		if (line[i][0] == 'A')
			check_object_ambient(line[i]);
		else if (line[i][0] == 'C')
			check_object_camera(line[i]);
		else if (line[i][0] == 'L')
			check_object_light(line[i]);
		else if (line[i][0] == 's' && line[i][1] == 'p')
			check_object_sp(line[i]);
		else if (line[i][0] == 'p' && line[i][1] == 'l')
			check_object_pl(line[i]);
		else if (line[i][0] == 'c' && line[i][1] == 'y')
			check_object_cy(line[i]);
		else if (line[i][0] == 'c' && line[i][1] == 'o')
			check_object_co(line[i]);
		else
			exit_with_error("invalid object\n");
		++i;
	}
	free_split(line);
}

void	validate_rt(char *str)
{
	check_invalid_char(str, "ACLsplcyo0123456789.,- \n");
	parse_object(str);
	if (check_cnt_ambient() != 1
		|| check_cnt_camera() != 1
		|| check_cnt_light() == 0)
		exit_with_error("invalid object count\n");
}
