/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subfmt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:18:03 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/07 11:31:09 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"
#include "subfmt.h"

const char	*get_flags(const char *fmt, t_fmtspec *sp)
{
	const char	*t;

	sp->flags = 0;
	while (*fmt && (t = ft_strchr(FLAGS, *fmt)))
	{
		sp->flags |= (0x1 << (t - FLAGS));
		fmt++;
	}
	if (sp->flags & FLG_PLUS && sp->flags & FLG_SPACE)
		sp->flags ^= FLG_SPACE;
	if (sp->flags & FLG_MINUS && sp->flags & FLG_ZERO)
		sp->flags ^= FLG_ZERO;
	return (fmt);
}

int			abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

const char	*get_precision(const char *fmt, int *n, va_list *ap)
{
	if (*fmt == '*')
	{
		*n = va_arg(*ap, int);
		return (fmt + 1);
	}
	*n = 0;
	while (ft_isdigit(*fmt))
	{
		*n = (*n * 10) + (*fmt - '0');
		fmt++;
	}
	return (fmt);
}

const char	*get_lenmod(const char *fmt, unsigned *lenmod)
{
	const char	mod[][3] = {
		"hh", "ll", "h", "l", "j", "t", "z"
	};
	const int	lmod[] = {
		2, 2, 1, 1, 1, 1, 1
	};
	int			i;

	*lenmod = 0;
	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(mod[i], fmt, lmod[i]) == 0)
		{
			*lenmod = 0x1 << i;
			return (fmt + lmod[i]);
		}
		i++;
	}
	return (fmt);
}
