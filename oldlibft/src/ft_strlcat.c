/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:31:18 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/01 09:26:58 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	l1;
	size_t	l2;
	size_t	ltot;

	l2 = ft_strlen(src);
	l1 = 0;
	while (dst[l1] && l1 < size)
		l1++;
	if (dst[l1] != '\0')
		return (size + l2);
	ltot = l1 + l2;
	while (*src && l1 < size - 1)
		dst[l1++] = *src++;
	dst[l1] = '\0';
	if (l1 < size - 1)
		return (l1);
	else
		return (ltot);
}
