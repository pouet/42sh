/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_insertat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 11:33:52 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/20 11:34:44 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			dll_insertat(t_dllist *lst, t_node *node, unsigned pos)
{
	t_node	*tmp;

	if (lst == NULL || node == NULL || pos > lst->sz)
		return (-1);
	if (pos == 0)
		return (dll_pushfront(lst, node));
	else if (pos == lst->sz)
		return (dll_pushback(lst, node));
	tmp = lst->first;
	while (pos-- != 0)
		tmp = tmp->next;
	node->next = tmp;
	node->prev = tmp->prev;
	tmp->prev->next = node;
	tmp->prev = node;
	lst->sz++;
	return (0);
}
