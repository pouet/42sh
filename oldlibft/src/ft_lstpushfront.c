/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 08:54:46 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/08 08:57:06 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstpushfront(t_list *l, t_list *el)
{
	if (l == NULL)
		return (el);
	else if (el == NULL)
		return (l);
	el->next = l;
	return (el);
}
