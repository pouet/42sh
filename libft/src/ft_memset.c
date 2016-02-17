/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 12:38:00 by nchrupal          #+#    #+#             */
/*   Updated: 2015/11/30 15:34:26 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*t;
	size_t			i;

	t = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		t[i] = c;
		i++;
	}
	return (b);
}
