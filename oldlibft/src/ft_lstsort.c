/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 10:59:05 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/14 11:00:02 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void		divide(t_list *base, t_list **l1, t_list **l2)
{
	t_list	*a;
	t_list	*b;

	if (base == NULL || base->next == NULL)
	{
		*l1 = base;
		*l2 = NULL;
		return ;
	}
	a = base;
	b = base->next;
	while (b)
	{
		b = b->next;
		if (b)
		{
			b = b->next;
			a = a->next;
		}
	}
	*l1 = base;
	*l2 = a->next;
	a->next = NULL;
}

static t_list	*merge(t_list *l1, t_list *l2,
		int (*cmp)(const void *, const void *))
{
	t_list	*ret;

	if (l1 == NULL)
		return (l2);
	else if (l2 == NULL)
		return (l1);
	ret = NULL;
	if (cmp(l1->content, l2->content) <= 0)
	{
		ret = l1;
		ret->next = merge(l1->next, l2, cmp);
	}
	else
	{
		ret = l2;
		ret->next = merge(l1, l2->next, cmp);
	}
	return (ret);
}

static void		ft_lstsort_rec(t_list **l,
		int (*cmp)(const void *, const void *))
{
	t_list	*a;
	t_list	*b;

	if (*l == NULL || (*l)->next == NULL)
		return ;
	divide(*l, &a, &b);
	ft_lstsort_rec(&a, cmp);
	ft_lstsort_rec(&b, cmp);
	*l = merge(a, b, cmp);
}

t_list			*ft_lstsort(t_list *base,
		int (*cmp)(const void *, const void *))
{
	if (base == NULL || cmp == NULL)
		return (NULL);
	ft_lstsort_rec(&base, cmp);
	return (base);
}
