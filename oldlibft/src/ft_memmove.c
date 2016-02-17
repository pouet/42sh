/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 14:41:10 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/07 14:41:33 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (s1 && s2)
	{
		str1 = (unsigned char *)s1;
		str2 = (unsigned char *)s2;
		if (s1 > s2)
		{
			str1 = str1 + n;
			str2 = str2 + n;
			while (n--)
				*--str1 = *--str2;
		}
		else
			ft_memcpy(s1, s2, n);
	}
	return (s1);
}
