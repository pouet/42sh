/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_createnode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 11:30:38 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/20 11:31:05 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_node		*dll_createnode(void *data, unsigned sz)
{
	t_node	*l;

	l = malloc(sizeof(*l));
	if (l == NULL)
		return (l);
	l->data = malloc(sz);
	if (l->data == NULL)
	{
		free(l);
		return (NULL);
	}
	ft_memcpy(l->data, data, sz);
	l->next = NULL;
	l->prev = NULL;
	return (l);
}
