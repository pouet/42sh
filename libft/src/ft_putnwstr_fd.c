/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnwstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:57:14 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/04 08:59:45 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_putnwstr_fd(wchar_t *s, int n, int fd)
{
	int		len;

	len = 0;
	while (*s && ft_wchar_len(*s) + len <= n)
	{
		len += ft_putwchar_fd(*s, fd);
		s++;
	}
	return (len);
}
