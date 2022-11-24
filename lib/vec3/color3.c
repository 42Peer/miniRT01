/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:21:32 by junkpark          #+#    #+#             */
/*   Updated: 2022/11/24 15:21:33 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_color3	color3(double r, double g, double b)
{
	t_color3	color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}
