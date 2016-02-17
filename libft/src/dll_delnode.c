/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_delnode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 11:35:05 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/20 11:35:21 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int			dll_delnode(t_dllist *lst, unsigned pos)
{
	t_node	*tmp;

	if (lst == NULL || pos >= lst->sz || lst->sz == 0)
		return (-1);
	tmp = lst->first;
	while (pos-- != 0)
		tmp = tmp->next;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (tmp == lst->first)
		lst->first = tmp->next;
	if (tmp == lst->last)
		lst->last = tmp->prev;
	free(tmp->data);
	free(tmp);
	lst->sz--;
	return (0);
}
