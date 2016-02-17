/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dou_p_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:03:57 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/07 11:42:13 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"
#include "dou_p_args.h"
#include "subfmt.h"
#include "int_args.h"

int		p_arg(const char **fmt, t_fmtspec *sp, va_list *ap, unsigned mod)
{
	sp->flags |= FLG_SHARP;
	mod = MOD_L;
	return (int_arg(fmt, sp, ap, mod));
}

int		dou_arg(const char **fmt, t_fmtspec *sp, va_list *ap, unsigned mod)
{
	char		s[2];
	char		*p;
	const char	**t;

	p = s;
	t = (const char **)&p;
	s[0] = ft_tolower(**fmt);
	s[1] = '\0';
	mod = MOD_L;
	return (int_arg(t, sp, ap, mod));
}
