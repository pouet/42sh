/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 08:56:22 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/27 09:44:15 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <term.h>
#include "signal_handler.h"
#include "initterms.h"
#include "print.h"
#include "print_items.h"
#include "get_cont.h"

extern t_sigvar g_sigvar;

void	sig_handler(int sig)
{
	char c;

	if (sig == SIGINT || sig == SIGQUIT || sig == SIGKILL || sig == SIGSTOP
			|| sig == SIGTERM)
	{
		clr_screen();
		unset_terms(&g_sigvar.old);
		exit(sig);
	}
	else if (sig == SIGTSTP)
	{
		c = g_sigvar.new.c_cc[VSUSP];
		clr_screen();
		unset_terms(&g_sigvar.old);
		signal(sig, SIG_DFL);
		ioctl(0, TIOCSTI, &c);
	}
	else if (sig == SIGCONT)
	{
		c = g_sigvar.new.c_cc[VEOL];
		set_terms(&g_sigvar.old, &g_sigvar.new);
		signal(SIGTSTP, sig_handler);
		ioctl(0, TIOCSTI, &c);
		print_cont(get_cont());
	}
}

void	sig_winch(int sig)
{
	if (sig == SIGWINCH)
	{
		check_changews(get_cont());
		print_cont(get_cont());
	}
}

void	check_changews(t_context *cont)
{
	struct winsize	ws;
	char			c;

	if (ioctl(0, TIOCGWINSZ, &ws) < 0)
		return ;
	if (ws.ws_row != cont->ws.ws_row || ws.ws_col != cont->ws.ws_col)
	{
		c = g_sigvar.new.c_cc[VEOL];
		ioctl(0, TIOCSTI, &c);
		cont->ws = ws;
		cont->li = cont->ws.ws_row - 3;
		cont->co = cont->ws.ws_col - 2;
	}
}

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGSTOP, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGKILL, sig_handler);
	signal(SIGCONT, sig_handler);
	signal(SIGWINCH, sig_winch);
}
