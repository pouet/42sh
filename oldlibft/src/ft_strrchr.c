/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:56:40 by nchrupal          #+#    #+#             */
/*   Updated: 2015/11/30 15:48:27 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*t;

	t = s;
	while (*t)
		t++;
	while (t >= s)
	{
		if (*t == (char)c)
			return ((char*)t);
		t--;
	}
	return (NULL);
}
