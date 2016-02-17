/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 09:53:27 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/11 09:11:10 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "error.h"
#include "ft_printf.h"

#define X(e, s) s,

char	*g_error[E_MAX + 1] = {
	EMACRO
};

#undef X

int		g_errno;

int		eprintf(char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	ft_vprintf_fd(fmt, ap, 2);
	va_end(ap);
	return (-1);
}
