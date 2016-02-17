/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 08:28:50 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/15 11:59:32 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	swap(void *p1, void *p2, void *tmp, size_t width)
{
	char	*s1;
	char	*s2;

	s1 = (char *)p1;
	s2 = (char *)p2;
	ft_memcpy(tmp, s1, width);
	ft_memcpy(s1, s2, width);
	ft_memcpy(s2, tmp, width);
}

void		ft_qsort(void *base, size_t nel, size_t width,
			int (*compar)(const void *, const void *))
{
	char	*cbase;
	char	*tmp;
	size_t	i;
	size_t	j;

	if (nel <= 1)
		return ;
	tmp = malloc(width * sizeof(*tmp));
	cbase = (char *)base;
	i = 1;
	j = 1;
	while (i < nel)
	{
		if (compar(cbase, cbase + (i * width)) > 0)
		{
			swap(cbase + (i * width), cbase + (j * width), tmp, width);
			j++;
		}
		i++;
	}
	swap(cbase, cbase + ((j - 1) * width), tmp, width);
	free(tmp);
	ft_qsort(cbase, j - 1, width, compar);
	ft_qsort(cbase + (j * width), nel - j, width, compar);
}
