/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_pushfront.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 11:31:16 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/20 11:31:42 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			dll_pushfront(t_dllist *lst, t_node *node)
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
		node->next = lst->first;
		lst->first = node;
		if (lst->first->next)
			lst->first->next->prev = lst->first;
	}
	lst->sz++;
	return (0);
}
