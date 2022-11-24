/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:19:29 by junkpark          #+#    #+#             */
/*   Updated: 2022/11/24 15:19:54 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wrap.h"

void	*wrap_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		exit_with_error("memory allocation failed\n");
	return (ret);
}
