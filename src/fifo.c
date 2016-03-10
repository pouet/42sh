/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:27:00 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 11:35:17 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "fifo.h"

const char *g_corr = "\"\"''``[](){}";

int		fifo_push(t_fifo *fifo, char c)
{
	char		*t;

	t = ft_strchr(g_corr, c);
	if (t == NULL)
		return (0);
	if (fifo->i + 1 >= BUFF_SZ)
	{
		eprintf("error: too many braces\n");
		return (0);
	}
	fifo->t[fifo->i++] = *(t + 1);
	return (1);
}

char	fifo_pop(t_fifo *fifo)
{
	if (fifo->i - 1 < 0)
		return ('\0');
	fifo->i--;
	return (fifo->t[fifo->i]);
}
