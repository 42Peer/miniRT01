/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:59:47 by mher              #+#    #+#             */
/*   Updated: 2022/11/09 12:02:34 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void        oadd(t_object **list, t_object *new_obj)
{
    t_object    *cur;

    if (*list == NULL)
    {
        *list = new_obj;
        return ;
    }
    cur = *list;
    while (cur->next)
        cur = cur->next;
    cur->next = new_obj;
}

t_object    *olast(t_object *list)
{
    if (list == NULL)
        return (NULL);
    while (list->next)
        list = list->next;
    return (list);
}
