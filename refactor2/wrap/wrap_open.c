/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:41:25 by jujeon            #+#    #+#             */
/*   Updated: 2022/11/24 15:41:25 by jujeon           ###   ########seoul.kr  */
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
