/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 09:45:52 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/07 14:31:26 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*t;
	char	*p;

	if (s == NULL || f == NULL)
		return (NULL);
	t = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (t == NULL)
		return (t);
	p = t;
	while (*s)
		*t++ = f(*s++);
	*t = '\0';
	return (p);
}
