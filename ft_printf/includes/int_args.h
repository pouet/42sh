/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_args.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:25:22 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/27 15:49:27 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_ARGS_H
# define INT_ARGS_H

# include <stdarg.h>
# include "subfmt.h"
# include "subfmt.h"

typedef struct		s_text
{
	char			snb[70];
	int				len;
	char			sign[5];
	int				neg;
}					t_text;

unsigned long long	get_int_fmt(unsigned mod, va_list *ap);
int					print_whitespace(int n, t_fmtspec *sp);
int					print_int_off(t_fmtspec *sp, unsigned long long n,
		t_text *t, int type);
int					print_int_cont(t_fmtspec *sp, t_text *t,
		unsigned long long n, int zero);
int					int_arg(const char **fmt, t_fmtspec *sp, va_list *ap,
		unsigned mod);

#endif
