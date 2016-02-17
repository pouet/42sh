/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 09:14:58 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/08 09:00:05 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*nxt;

	if (del == NULL || alst == NULL || *alst == NULL)
		return (-1);
	while (*alst != NULL)
	{
		nxt = (*alst)->next;
		ft_lstdelone(alst, del);
		*alst = nxt;
	}
	return (0);
}
