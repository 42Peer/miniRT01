/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:20:12 by junkpark          #+#    #+#             */
/*   Updated: 2022/11/24 15:20:12 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	set_filter(int *filter, const char *valid_char)
{
	const int	v_len = ft_strlen(valid_char);
	int			i;

	i = 0;
	while (i < 128)
	{
		filter[i] = 0;
		i++;
	}
	i = 0;
	while (i < v_len)
	{
		filter[(int)valid_char[i]] += 1;
		i++;
	}
}
