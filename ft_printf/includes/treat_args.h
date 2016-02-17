/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_args.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:19:57 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/07 11:40:58 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREAT_ARGS_H
# define TREAT_ARGS_H

# include <stdarg.h>
# include "subfmt.h"

int			pct_arg(const char **fmt, t_fmtspec *sp, va_list *ap, unsigned mod);
int			print_no_arg(const char **fmt, t_fmtspec *sp);
const char	*treat_arg(const char *s, t_fmtspec *sp, int *n, va_list *ap);
int			print_args(const char **fmt, va_list *ap);

#endif
