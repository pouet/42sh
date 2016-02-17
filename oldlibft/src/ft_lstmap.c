/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 09:27:59 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/02 10:07:39 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*p;
	t_list	*nxt;
	t_list	*tmp;

	if (lst == NULL || f == NULL)
		return (NULL);
	p = NULL;
	nxt = NULL;
	while (lst)
	{
		tmp = f(lst);
		if (tmp == NULL)
			return (NULL);
		if (p == NULL)
			p = ft_lstnew(tmp->content, tmp->content_size);
		else
		{
			nxt = p;
			while (nxt->next != NULL)
				nxt = nxt->next;
			nxt->next = ft_lstnew(tmp->content, tmp->content_size);
		}
		lst = lst->next;
	}
	return (p);
}
