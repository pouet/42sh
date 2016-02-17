/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 13:35:55 by nchrupal          #+#    #+#             */
/*   Updated: 2015/11/30 15:36:37 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*t;
	unsigned char		a;
	size_t				i;

	t = (const unsigned char*)s;
	a = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (t[i] == a)
			return ((void*)(t + i));
		i++;
	}
	return (NULL);
}
