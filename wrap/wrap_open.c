/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:19:21 by junkpark          #+#    #+#             */
/*   Updated: 2022/11/24 15:19:50 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wrap.h"

int	wrap_open(const char *pathname, int flags)
{
	int	fd;

	fd = open(pathname, flags);
	if (fd == -1)
		exit_with_error("file open fail\n");
	return (fd);
}
