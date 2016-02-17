/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:08:43 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/04 08:52:26 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"
#include "int_args.h"
#include "int_form.h"
#include "subfmt.h"
#include "fd.h"

unsigned long long	get_int_fmt(unsigned mod, va_list *ap)
{
	unsigned long long	n;

	if (mod == MOD_L)
		n = va_arg(*ap, unsigned long);
	else if (mod == MOD_LL || mod == MOD_Z || mod == MOD_J)
		n = va_arg(*ap, unsigned long long);
	else
	{
		n = va_arg(*ap, unsigned int);
		if (mod == MOD_HH)
			n = n & 0xFF;
		else if (mod == MOD_H)
			n = n & 0xFFFF;
	}
	return (n);
}

int					print_whitespace(int n, t_fmtspec *sp)
{
	int		i;
	char	c;

	if (n < 0)
		n = 0;
	c = ' ';
	if (sp->flags & FLG_ZERO)
		c = '0';
	i = 0;
	while (i < n)
	{
		ft_putchar_fd(c, get_fd());
		i++;
	}
	return (n);
}

int					print_int_off(t_fmtspec *sp, unsigned long long n,
		t_text *t, int type)
{
	int lenzero;
	int lenspace;
	int	ret;

	ret = 0;
	calc_len_space(sp, t, &lenzero, &lenspace);
	if (type == 1 && lenspace > 0)
	{
		lenzero = sp->flags;
		if (sp->fld_w > 0 && sp->prec > 0 && sp->fld_w > sp->prec && n < 10)
			sp->flags = 0;
		ret = print_whitespace(lenspace, sp);
		sp->flags = lenzero;
	}
	else if (type == 0 && lenzero > 0)
	{
		sp->flags |= FLG_ZERO;
		ret = print_whitespace(lenzero, sp);
		sp->flags ^= FLG_ZERO;
	}
	return (ret);
}

int					print_int_cont(t_fmtspec *sp, t_text *t,
		unsigned long long n, int zero)
{
	int		tot;
	int		a;

	a = 0;
	tot = 0;
	if (t->neg && t->len + t->neg <= sp->fld_w && sp->prec <= 0 && zero)
	{
		ft_putstr_fd(t->sign, get_fd());
		a = 1;
	}
	if ((sp->flags & FLG_MINUS) == 0)
		tot += print_int_off(sp, n, t, 1);
	if (a == 0)
		ft_putstr_fd(t->sign, get_fd());
	if (sp->prec == 0 && n == 0)
		t->len = 0;
	else
	{
		tot += print_int_off(sp, n, t, 0);
		tot += t->len;
		ft_putstr_fd(t->snb, get_fd());
	}
	if (sp->flags & FLG_MINUS)
		tot += print_int_off(sp, n, t, 1);
	return (tot);
}

int					int_arg(const char **fmt, t_fmtspec *sp, va_list *ap,
		unsigned mod)
{
	unsigned long long	n;
	t_text				t;

	n = get_int_fmt(mod, ap);
	t.neg = get_int_sign(**fmt, t.sign, mod, &n);
	t.neg += set_int_form(t.sign, **fmt, sp, n != 0);
	t.sign[t.neg] = '\0';
	t.len = ull_to_str(t.snb, n, **fmt);
	t.snb[t.len] = '\0';
	return (print_int_cont(sp, &t, n, (sp->flags & FLG_ZERO)) + t.neg);
}
