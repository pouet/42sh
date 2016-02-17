/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:56:34 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/07 12:00:09 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_putwstr(wchar_t *s)
{
	int		len;

	len = 0;
	while (*s)
	{
		len += ft_putwchar(*s);
		s++;
	}
	return (len);
}
