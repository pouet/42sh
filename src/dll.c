/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 09:13:25 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/25 12:48:15 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "dll.h"

int		max_len(t_dllist *l)
{
	t_node	*n;
	int		len;

	len = 0;
	n = l->first;
	while (n)
	{
		if (((t_choice *)n->data)->len > len)
			len = ((t_choice *)n->data)->len;
		n = n->next;
	}
	return (len);
}

t_node	*dll_next(t_node *cur, int inc)
{
	if (inc < 0)
		return (cur->prev);
	else
		return (cur->next);
}

t_node	*dll_move(t_dllist *l, t_node *cur, int n, int *index)
{
	int		inc;

	if (n < 0)
		inc = 1;
	else
		inc = -1;
	*index = (*index + n);
	if (*index < 0)
		*index += l->sz;
	else
		*index %= l->sz;
	while (cur && n != 0)
	{
		cur = dll_next(cur, n);
		if (cur == NULL && n < 0)
			cur = l->last;
		else if (cur == NULL && n > 0)
			cur = l->first;
		n += inc;
	}
	return (cur);
}
