/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:02:20 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/01 11:38:35 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char	*s;
	size_t	i;

	i = 0;
	s = dst;
	while (i < n && (*s++ = *(char*)src++))
		i++;
	while (i++ < n)
		*s++ = '\0';
	return (dst);
}
