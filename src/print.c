/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 12:03:43 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/23 10:08:58 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "libft.h"
#include "print.h"
#include "tty.h"

int		ft_putchar_tty(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

void	ft_tputs(char *s)
{
	s = tgetstr(s, NULL);
	tputs(s, 1, ft_putchar_tty);
}

void	clr_screen(void)
{
	ft_tputs(CLRSCR);
}

void	mv_cur(char *cap, int hpos, int vpos)
{
	char		*s;

	s = tgetstr(cap, NULL);
	s = tgoto(s, hpos, vpos);
	tputs(s, 1, ft_putchar_tty);
}

void	print_txt(char *s, int hpos, int vpos, unsigned type)
{
	if (type & TXT_RVID)
		ft_tputs(SRVIDEO);
	if (type & TXT_UDRL)
		ft_tputs(SUNDERL);
	mv_cur("cm", hpos, vpos);
	ft_putstr_fd(s, 1);
	ft_tputs(URVIDEO);
	ft_tputs(UUNDERL);
}
