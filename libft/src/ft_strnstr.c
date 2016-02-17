/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 15:04:39 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/01 13:02:03 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	size_t		j;

	if (*s2 == '\0')
		return ((char*)s1);
	j = 0;
	while (*s1 && j < n)
	{
		i = 0;
		while (i + j < n && s1[i] && s2[i] && s1[i] == s2[i])
			i++;
		if (s2[i] == '\0')
			return ((char*)s1);
		s1++;
		j++;
	}
	return (NULL);
}
