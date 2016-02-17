/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnwstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:57:14 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/04 08:59:53 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_putnwstr(wchar_t *s, int n)
{
	int		len;

	len = 0;
	while (*s && ft_wchar_len(*s) + len <= n)
	{
		len += ft_putwchar(*s);
		s++;
	}
	return (len);
}
