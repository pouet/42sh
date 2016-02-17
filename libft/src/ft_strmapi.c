/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 09:52:26 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/07 14:31:20 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*t;
	char			*p;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	t = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (t == NULL)
		return (t);
	p = t;
	i = 0;
	while (*s)
		*t++ = f(i++, *s++);
	*t = '\0';
	return (p);
}
