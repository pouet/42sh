/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 09:01:00 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/07 14:25:48 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*p;

	p = (t_list*)malloc(sizeof(*p));
	if (p == NULL)
		return (p);
	if (content == NULL || content_size == 0)
	{
		p->content = NULL;
		p->content_size = 0;
	}
	else
	{
		p->content = malloc(content_size);
		if (p->content == NULL)
		{
			free(p);
			return (NULL);
		}
		ft_memcpy(p->content, content, content_size);
		p->content_size = content_size;
	}
	p->next = NULL;
	return (p);
}
