/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 09:57:24 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/01 10:26:17 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*t;
	size_t	i;

	if (s == NULL)
		return (NULL);
	t = ft_strnew(len + 1);
	if (t == NULL)
		return (t);
	i = 0;
	while (i < len)
	{
		t[i] = s[start + i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
