/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 12:50:57 by nchrupal          #+#    #+#             */
/*   Updated: 2015/11/30 15:43:37 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*t;
	const unsigned char	*u;
	size_t				i;

	t = (unsigned char*)dst;
	u = (const unsigned char*)src;
	i = 0;
	while (i < n)
	{
		t[i] = (unsigned char)u[i];
		i++;
	}
	return (dst);
}
