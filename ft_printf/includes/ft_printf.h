/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 14:36:50 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/17 11:12:12 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int		ft_printf(const char *fmt, ...);
int		ft_printf_fd(int fd, const char *fmt, ...);
int		ft_vprintf(const char *fmt, va_list ap);
int		ft_vprintf_fd(const char *fmt, va_list ap, int fd);

#endif
