/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:10:45 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/07 14:31:33 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	cntword(char const *s, char c)
{
	int	n;

	n = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s != '\0')
			n++;
		while (*s && *s != c)
			s++;
	}
	return (n);
}

static int	lenword(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**t;
	int		nword;
	int		i;
	size_t	len;

	if (s == NULL)
		return (NULL);
	nword = cntword(s, c);
	if ((t = (char**)malloc((nword + 1) * sizeof(*t))) == NULL)
		return (NULL);
	t[nword] = NULL;
	i = 0;
	while (i < nword)
	{
		while (*s == c)
			s++;
		len = lenword(s, c);
		if ((t[i] = (char *)malloc((len + 1) * sizeof(**t))) == NULL)
			return (NULL);
		ft_strncpy(t[i], s, len);
		s += len;
		t[i++][len] = '\0';
	}
	return (t);
}
