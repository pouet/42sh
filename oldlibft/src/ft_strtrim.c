/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 10:07:52 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/07 14:31:47 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	strlentrim(char const *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (j > i && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
		j--;
	return (j - i + 1);
}

char		*ft_strtrim(char const *s)
{
	char	*t;
	size_t	i;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = strlentrim(s);
	t = (char*)malloc(len * sizeof(char));
	if (t == NULL)
		return (t);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	i = 0;
	while (i < len)
	{
		t[i] = s[i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
