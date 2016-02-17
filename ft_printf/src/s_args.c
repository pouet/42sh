/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_args.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 10:15:16 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/04 08:55:08 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"
#include "s_args.h"
#include "int_args.h"
#include "fd.h"

int		wc_arg(const char **fmt, t_fmtspec *sp, va_list *ap, unsigned mod)
{
	wchar_t			c;
	int				len;

	(void)fmt;
	(void)mod;
	c = va_arg(*ap, wchar_t);
	len = ft_wchar_len(c);
	if ((sp->flags & FLG_MINUS) == 0)
		len += print_whitespace(sp->fld_w - len, sp);
	ft_putwchar_fd(c, get_fd());
	if (sp->flags & FLG_MINUS)
		len += print_whitespace(sp->fld_w - len, sp);
	return (len);
}

int		c_arg(const char **fmt, t_fmtspec *sp, va_list *ap, unsigned mod)
{
	unsigned char	c;
	int				len;

	(void)fmt;
	len = 0;
	if (mod == 0 && **fmt == 'c')
	{
		c = va_arg(*ap, unsigned int);
		len = 1;
		if ((sp->flags & FLG_MINUS) == 0)
			len += print_whitespace(sp->fld_w - len, sp);
		ft_putchar_fd(c, get_fd());
		if (sp->flags & FLG_MINUS)
			len += print_whitespace(sp->fld_w - len, sp);
	}
	else
		len = wc_arg(fmt, sp, ap, mod);
	return (len);
}

int		reduce_wstr(wchar_t *s, int len, int n)
{
	int		i;

	if (n >= 0 && len > n)
		len = n;
	i = 0;
	n = 0;
	while (n + ft_wchar_len(s[i]) <= len)
	{
		n += ft_wchar_len(s[i]);
		i++;
	}
	return (n);
}

int		ws_arg(const char **fmt, t_fmtspec *sp, va_list *ap, unsigned mod)
{
	int				len;
	int				tot;
	wchar_t			*s;

	(void)fmt;
	(void)mod;
	(void)sp;
	len = 0;
	s = NULL;
	tot = 0;
	s = va_arg(*ap, wchar_t *);
	if (s == NULL)
	{
		ft_putstr_fd("(null)", get_fd());
		return (6);
	}
	len = ft_wstrlen(s);
	if (sp->prec >= 0 && len > sp->prec)
		len = reduce_wstr(s, len, sp->prec);
	if ((sp->flags & FLG_MINUS) == 0)
		tot += print_whitespace(sp->fld_w - len, sp);
	tot += ft_putnwstr_fd(s, len, get_fd());
	if (sp->flags & FLG_MINUS)
		tot += print_whitespace(sp->fld_w - len, sp);
	return (tot);
}

int		s_arg(const char **fmt, t_fmtspec *sp, va_list *ap, unsigned mod)
{
	int				len;
	int				tot;
	char			*s;

	if (mod == MOD_L)
		return (ws_arg(fmt, sp, ap, mod));
	len = 0;
	tot = 0;
	s = va_arg(*ap, char *);
	if (s == NULL && sp->prec < 0)
	{
		ft_putstr_fd("(null)", get_fd());
		return (6);
	}
	else if (s == NULL && sp->prec >= 0)
		s = "";
	len = ft_strlen(s);
	if (sp->prec >= 0 && len > sp->prec)
		len = sp->prec;
	if ((sp->flags & FLG_MINUS) == 0)
		tot += print_whitespace(sp->fld_w - len, sp);
	tot += ft_putnstr_fd(s, len, get_fd());
	if (sp->flags & FLG_MINUS)
		tot += print_whitespace(sp->fld_w - len, sp);
	return (tot);
}
