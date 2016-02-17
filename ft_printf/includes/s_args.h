/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_args.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:21:59 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/07 11:32:34 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_ARGS_H
# define S_ARGS_H

# include <stdarg.h>
# include "subfmt.h"

int		wc_arg(const char **fmt, t_fmtspec *sp, va_list *ap, unsigned mod);
int		c_arg(const char **fmt, t_fmtspec *sp, va_list *ap, unsigned mod);
int		reduce_wstr(wchar_t *s, int len, int n);
int		ws_arg(const char **fmt, t_fmtspec *sp, va_list *ap, unsigned mod);
int		s_arg(const char **fmt, t_fmtspec *sp, va_list *ap, unsigned mod);

#endif
