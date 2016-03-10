/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initterms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 11:56:04 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 08:55:10 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <stdlib.h>
#include <term.h>
#include <unistd.h>
#include "libft.h"
#include "initterms.h"
#include "print.h"
#include "xmalloc.h"

struct termios g_old;

/*
** Just for norminette...
*/
#define VARPC extern char PC
#define VARUP extern char *UP
#define VARBC extern char *BC

int		init_term(void)
{
	char	*term;
	char	bp;

	term = getenv("TERM");
	if (term == NULL || term[5] == '\0')
		term = "TERM=xterm-256color";
	if (tgetent(&bp, term) == ERR)
	{
		ft_putendl_fd("terminfo database could not be found", 2);
		return (-1);
	}
	if (!isatty(0))
	{
		ft_putendl_fd("not a tty", 2);
		return (-1);
	}
	return (0);
}

void	set_extern_var(void)
{
	extern short	ospeed;

	VARPC;
	VARUP;
	VARBC;
	BC = tgetstr("pc", NULL);
	PC = BC ? *BC : 0;
	BC = tgetstr("le", NULL);
	UP = tgetstr("up", NULL);
	ospeed = 9600;
}

void	set_terms(void)
{
	struct termios new;

	tcgetattr(0, &g_old);
	new = g_old;
	new.c_lflag &= ~(ICANON | ECHO);
	new.c_cc[VTIME] = 0;
	new.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new);
	ft_tputs(SKEYPAD);
	ft_tputs(CURVI);
}

void	unset_terms(void)
{
	ft_tputs(UKEYPAD);
	tcsetattr(0, TCSANOW, &g_old);
}
