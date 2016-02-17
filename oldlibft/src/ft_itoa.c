/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:32:46 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/07 14:25:10 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	convert(char *t, int n)
{
	long long	n1;
	int			sign;
	int			i;

	n1 = n;
	sign = 1;
	if (n1 < 0)
	{
		sign = -1;
		n1 = -n1;
	}
	i = 0;
	if (n1 == 0)
		i = 1;
	t[0] = '0';
	while (n1 != 0)
	{
		t[i] = (n1 % 10) + '0';
		n1 /= 10;
		i++;
	}
	if (sign < 0)
		t[i++] = '-';
	t[i] = '\0';
}

char		*ft_itoa(int n)
{
	char	t[15];
	char	*s;
	int		len;
	int		i;

	convert(t, n);
	len = ft_strlen(t);
	s = (char *)malloc((len + 1) * sizeof(*s));
	if (s == NULL)
		return (s);
	i = 0;
	while (i < len)
	{
		s[i] = t[len - i - 1];
		i++;
	}
	s[i] = '\0';
	return (s);
}
