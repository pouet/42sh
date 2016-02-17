/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_dellist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 11:29:57 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/20 11:30:16 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		dll_dellist(t_dllist *lst)
{
	t_node	*tmp;

	if (lst == NULL)
		return ;
	tmp = lst->first;
	while (tmp)
	{
		lst->first = tmp->next;
		free(tmp->data);
		free(tmp);
		tmp = lst->first;
	}
	free(lst);
}
