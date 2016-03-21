/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 15:11:40 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/21 17:43:40 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && *s1 && *s1 == *s2)
	{
		i++;
		s1++;
		s2++;
	}
	if (i == n)
		return (0);
	else
		return ((unsigned char)*s1 - (unsigned char)*s2);
}
