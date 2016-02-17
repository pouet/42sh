/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:59:32 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/01 11:47:27 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t		i;

	if (*s2 == '\0')
		return ((char*)s1);
	while (*s1)
	{
		i = 0;
		while (s1[i] && s2[i] && s1[i] == s2[i])
			i++;
		if (s2[i] == '\0')
			return ((char*)s1);
		s1++;
	}
	return (NULL);
}
