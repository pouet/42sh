/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dou_p_args.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:23:47 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/07 11:38:39 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOU_P_ARGS_H
# define DOU_P_ARGS_H

# include <stdarg.h>
# include "subfmt.h"
# include "subfmt.h"

int		p_arg(const char **fmt, t_fmtspec *sp, va_list *ap, unsigned mod);
int		dou_arg(const char **fmt, t_fmtspec *sp, va_list *ap, unsigned mod);

#endif
