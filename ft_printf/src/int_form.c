/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_form.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:11:24 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/27 15:45:28 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"
#include "subfmt.h"
#include "int_form.h"
#include "int_args.h"

void	set_sign(int *len, char *form, unsigned mod, unsigned long long *n)
{
	if (mod == MOD_HH && (char)*n < 0)
	{
		*n = -(char)*n;
		form[(*len)++] = '-';
	}
	else if (mod == MOD_H && (short)*n < 0)
	{
		*n = -(short)*n;
		form[(*len)++] = '-';
	}
	else if (mod == MOD_L && (long)*n < 0)
	{
		*n = -(long)*n;
		form[(*len)++] = '-';
	}
	else if ((mod & (MOD_LL | MOD_J | MOD_Z)) && (long long)*n < 0)
	{
		*n = -(long long)*n;
		form[(*len)++] = '-';
	}
	else if (mod == 0 && (int)*n < 0)
	{
		*n = (-(int)*n) & ~(~0ULL << (sizeof(int) * 8));
		form[(*len)++] = '-';
	}
}

int		get_int_sign(char c, char *form, unsigned mod, unsigned long long *n)
{
	int			len;

	len = 0;
	if (c == 'd' || c == 'i')
		set_sign(&len, form, mod, n);
	form[len] = '\0';
	return (len);
}

int		ull_to_str(char *s, unsigned long long n, char c)
{
	int						len;
	unsigned long long		base;

	len = 0;
	base = 10;
	if (c == 'b')
		base = 2;
	else if (c == 'o')
		base = 8;
	else if (c == 'x' || c == 'X' || c == 'p')
		base = 16;
	if (n >= base)
		len = ull_to_str(s, n / base, c);
	if (c == 'x' || c == 'p')
		s[len] = "0123456789abcdef"[n % base];
	else
		s[len] = "0123456789ABCDEF"[n % base];
	return (len + 1);
}

int		set_int_form(char *form, char fmt, t_fmtspec *sp, int n)
{
	int		len;

	len = 0;
	if (form[0] == '-')
		len = 0;
	else if ((sp->flags & FLG_PLUS) && fmt != 'o' && fmt != 'x' && fmt != 'X' &&
			fmt != 'p' && fmt != 'u')
		form[len++] = '+';
	else if ((sp->flags & FLG_SPACE) && (fmt == 'd' || fmt == 'i'))
		form[len++] = ' ';
	if (fmt == 'p')
	{
		form[len++] = '0';
		form[len++] = 'x';
	}
	if ((sp->flags & FLG_SHARP) &&
		(n != 0 || (n == 0 && sp->prec == 0 && fmt == 'o'))
		&& (fmt == 'o' || fmt == 'x' || fmt == 'X' || fmt == 'b'))
	{
		form[len++] = '0';
		if (fmt == 'x' || fmt == 'X' || fmt == 'b')
			form[len++] = fmt;
	}
	return (len);
}

void	calc_len_space(t_fmtspec *sp, t_text *t, int *lenzero, int *lenspace)
{
	*lenzero = 0;
	*lenspace = 0;
	if (t->len > 0 && sp->prec == 0 && sp->fld_w > 0)
		t->len = 0;
	if (ft_strcmp(t->sign, "0") == 0 && sp->prec > t->len + t->neg)
		*lenzero = sp->prec - (t->len + t->neg);
	else if (sp->prec > t->len)
		*lenzero = sp->prec - t->len;
	if (sp->fld_w > *lenzero + t->len + t->neg)
		*lenspace = sp->fld_w - (*lenzero + t->len + t->neg);
}
