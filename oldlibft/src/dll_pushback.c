/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_pushback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 11:31:48 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/20 11:33:32 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			dll_pushback(t_dllist *lst, t_node *node)
{
	if (lst == NULL || node == NULL)
		return (-1);
	if (lst->sz == 0)
	{
		lst->first = node;
		lst->last = node;
	}
	else
	{
		node->prev = lst->last;
		lst->last = node;
		if (lst->last->prev)
			lst->last->prev->next = lst->last;
	}
	lst->sz++;
	return (0);
}
