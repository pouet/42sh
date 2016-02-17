/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 12:57:37 by nchrupal          #+#    #+#             */
/*   Updated: 2015/11/30 15:43:09 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*t;
	const unsigned char	*u;
	unsigned char		a;
	size_t				i;

	t = (unsigned char*)dst;
	u = (const unsigned char*)src;
	a = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		t[i] = (unsigned char)u[i];
		if (a == u[i])
			return ((void*)(t + i + 1));
		i++;
	}
	return (NULL);
}
