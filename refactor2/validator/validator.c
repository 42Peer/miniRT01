/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnam <jnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 01:44:16 by mher              #+#    #+#             */
/*   Updated: 2022/11/18 16:56:29 by jnam             ###   ########.fr       */
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
