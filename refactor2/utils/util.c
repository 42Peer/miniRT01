/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:41:01 by jujeon            #+#    #+#             */
/*   Updated: 2022/11/24 15:41:01 by jujeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	exit_with_error(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

int	get_file_size(char *filename)
{
	int		count;
	int		fd;
	int		read_byte;
	char	buff[1024];

	read_byte = 1;
	count = 0;
	fd = wrap_open(filename, O_RDONLY);
	while (read_byte)
	{
		read_byte = read(fd, buff, 1024);
		count += read_byte;
	}
	close(fd);
	return (count);
}

void	free_split(char **data)
{
	char	**cur;

	cur = data;
	while (*cur)
	{
		free(*cur);
		cur++;
	}
	free(data);
}
