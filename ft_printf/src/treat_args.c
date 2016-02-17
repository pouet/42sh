/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 10:11:16 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/04 08:55:45 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"
#include "subfmt.h"
#include "treat_args.h"
#include "int_args.h"
#include "dou_p_args.h"
#include "s_args.h"
#include "fd.h"

static const t_conv	g_conv[] = {
	{ "bdiouxX", int_arg },
	{ "DOU", dou_arg },
	{ "Cc", c_arg },
	{ "s", s_arg },
	{ "S", ws_arg },
	{ "p", p_arg },
	{ "%", pct_arg }
};

int					pct_arg(const char **fmt, t_fmtspec *sp, va_list *ap,
		unsigned mod)
{
	int		len;

	(void)fmt;
	(void)ap;
	(void)mod;
	len = 1;
	if ((sp->flags & FLG_MINUS) == 0)
		len += print_whitespace(sp->fld_w - len, sp);
	ft_putchar_fd('%', get_fd());
	if (sp->flags & FLG_MINUS)
		len += print_whitespace(sp->fld_w - len, sp);
	return (len);
}

int					print_no_arg(const char **fmt, t_fmtspec *sp)
{
	int		len;

	len = 1;
	if ((sp->flags & FLG_MINUS) == 0)
		len += print_whitespace(sp->fld_w - 1, sp);
	ft_putchar_fd(**fmt, get_fd());
	if (sp->flags & FLG_MINUS)
		len += print_whitespace(sp->fld_w - 1, sp);
	return (len);
}

const char			*treat_arg(const char *s, t_fmtspec *sp, int *n,
		va_list *ap)
{
	unsigned		mod;
	unsigned		i;

	s = get_lenmod(s, &mod);
	i = 0;
	while (*s && i < sizeof(g_conv) / sizeof(*g_conv))
	{
		if (ft_strchr(g_conv[i].spec, *s))
		{
			*n = g_conv[i].f(&s, sp, ap, mod);
			s++;
			break ;
		}
		i++;
	}
	if (*s && i == sizeof(g_conv) / sizeof(*g_conv))
	{
		*n = print_no_arg(&s, sp);
		s++;
	}
	return (s);
}

int					print_args(const char **fmt, va_list *ap)
{
	int			n;
	const char	*s;
	t_fmtspec	sp;

	s = *fmt;
	n = 0;
	s = get_flags(s, &sp);
	sp.fld_w = 0;
	while (*s && (*s == '*' || ft_isdigit(*s)))
		s = get_precision(s, &sp.fld_w, ap);
	if (*s == '.')
	{
		s++;
		s = get_precision(s, &sp.prec, ap);
	}
	else
		sp.prec = -1;
	if (sp.fld_w < 0)
	{
		sp.fld_w = abs(sp.fld_w);
		sp.flags |= FLG_MINUS;
	}
	s = treat_arg(s, &sp, &n, ap);
	*fmt = s;
	return (n);
}
