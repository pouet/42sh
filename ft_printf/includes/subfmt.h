/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subfmt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:28:49 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/07 11:31:43 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBFMT_H
# define SUBFMT_H

# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

# define FLAGS "#-+ 0"

# define FLG_SHARP (0x1 << 0)
# define FLG_MINUS (0x1 << 1)
# define FLG_PLUS  (0x1 << 2)
# define FLG_SPACE (0x1 << 3)
# define FLG_ZERO  (0x1 << 4)

# define MOD_HH (0x1 << 0)
# define MOD_LL (0x1 << 1)
# define MOD_H  (0x1 << 2)
# define MOD_L  (0x1 << 3)
# define MOD_J  (0x1 << 4)
# define MOD_T  (0x1 << 5)
# define MOD_Z  (0x1 << 6)

typedef struct		s_fmtspec
{
	unsigned		flags;
	int				fld_w;
	int				prec;
}					t_fmtspec;

typedef struct		s_conv
{
	const char		*spec;
	int				(*f)(const char **, t_fmtspec *, va_list *, unsigned);
}					t_conv;

const char			*get_flags(const char *fmt, t_fmtspec *sp);
int					abs(int n);
const char			*get_precision(const char *fmt, int *n, va_list *ap);
const char			*get_lenmod(const char *fmt, unsigned *lenmod);

#endif
