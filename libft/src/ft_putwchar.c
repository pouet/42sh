/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:55:43 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/04 09:16:24 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_putwchar(wchar_t c)
{
	int		len;

	len = ft_wchar_len(c);
	if (len == 1)
		ft_putchar(c);
	else if (len == 2)
	{
		ft_putchar(((c & 0x000007C0) >> 6) | 0xC0);
		ft_putchar((c & 0x0000003F) | 0x80);
	}
	else if (len == 3)
	{
		ft_putchar(((c & 0x0000F000) >> 12) | 0xE0);
		ft_putchar(((c & 0x00000FC0) >> 6) | 0x80);
		ft_putchar((c & 0x0000003F) | 0x80);
	}
	else if (len == 4)
	{
		ft_putchar(((c & 0x001C0000) >> 18) | 0xF0);
		ft_putchar(((c & 0x0003F000) >> 12) | 0x80);
		ft_putchar(((c & 0x00000FC0) >> 6) | 0x80);
		ft_putchar((c & 0x0000003F) | 0x80);
	}
	return (len);
}
