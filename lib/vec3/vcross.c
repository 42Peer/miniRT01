/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vcross.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:21:38 by junkpark          #+#    #+#             */
/*   Updated: 2022/11/24 15:22:13 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vcross(t_vec3 vec, t_vec3 vec2)
{
	t_vec3	new;

	new.x = vec.y * vec2.z - vec.z * vec2.y;
	new.y = vec.z * vec2.x - vec.x * vec2.z;
	new.z = vec.x * vec2.y - vec.y * vec2.x;
	return (new);
}
