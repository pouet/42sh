/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 15:11:58 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/07 15:18:12 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstpushback(t_list *l, t_list *new)
{
	t_list	*iter;

	if (l == NULL)
		l = new;
	else
	{
		iter = l;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new;
	}
	return (l);
}
