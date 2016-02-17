/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:21:55 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/09 08:58:46 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"
#include "treat_args.h"
#include "colors.h"
#include "fd.h"

int		ft_vprintf_fd(const char *fmt, va_list ap, int fd)
{
	int			n;

	if (fd < 0 || fd > 0xFF)
		return (-1);
	set_fd(fd);
	n = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			n += print_args(&fmt, (va_list*)ap);
		}
		else if (*fmt == '{')
			n += color_args(&fmt);
		else
		{
			ft_putchar_fd(*fmt, get_fd());
			fmt++;
			n++;
		}
	}
	return (n);
}

int		ft_vprintf(const char *fmt, va_list ap)
{
	return (ft_vprintf_fd(fmt, ap, 1));
}

int		ft_printf(const char *fmt, ...)
{
	va_list		ap;
	int			n;

	n = 0;
	va_start(ap, fmt);
	n = ft_vprintf_fd(fmt, ap, 1);
	va_end(ap);
	return (n);
}

int		ft_printf_fd(int fd, const char *fmt, ...)
{
	va_list		ap;
	int			n;

	n = 0;
	va_start(ap, fmt);
	n = ft_vprintf_fd(fmt, ap, fd);
	va_end(ap);
	return (n);
}
