/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:22:49 by junkpark          #+#    #+#             */
/*   Updated: 2022/11/24 15:22:49 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAP_H
# define WRAP_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/syslimits.h>
# include "minirt.h"

void	*wrap_malloc(size_t size);
int		wrap_open(const char *pathname, int flags);

#endif
