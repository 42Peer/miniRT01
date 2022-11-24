/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:21:52 by junkpark          #+#    #+#             */
/*   Updated: 2022/11/24 15:22:09 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vmin(t_vec3 vec1, t_vec3 vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}
