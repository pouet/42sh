/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 10:06:17 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/27 09:32:09 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "signal_handler.h"
#include "initterms.h"
#include "events.h"
#include "print.h"
#include "print_items.h"
#include "context.h"
#include "search.h"
#include "get_cont.h"
#include "tty.h"

t_sigvar g_sigvar;

t_context	*get_cont(void)
{
	static t_context	cont;

	return (&cont);
}

int			apply_events(t_context *cont, t_events *ev)
{
	if (ev->type == T_KEYS)
	{
		cont->srch.found = -1;
		if (keyisarrow(ev))
			move_key(cont, ev);
		else if (ev->c == K_DEL || ev->c == K_BCKSP)
			delchoice(cont);
		else if (ev->c == K_ENTER)
			return (1);
		else if (ev->c == K_ESCAP)
			return (0);
		else if (ev->c == K_SPACE)
			selchoice(cont);
	}
	else
		search(cont, ev);
	return (-1);
}

int			main_loop(t_context *cont)
{
	t_events		ev;
	int				ret;
	int				ret_ev;

	while (cont->l->sz > 0 && ret >= 0)
	{
		if ((ret = getevents(&ev)) > 0)
		{
			ret_ev = apply_events(cont, &ev);
			if (ret_ev >= 0)
				return (ret_ev);
			print_cont(cont);
		}
	}
	return (0);
}

int			main(int ac, char **av)
{
	int				ret;

	if (ac == 1)
		return (0);
	if (init_term() < 0)
		return (1);
	init_context(get_cont(), ac, av);
	set_terms(&g_sigvar.old, &g_sigvar.new);
	set_extern_var();
	set_signal();
	check_changews(get_cont());
	print_cont(get_cont());
	ret = main_loop(get_cont());
	clr_screen();
	unset_terms(&g_sigvar.old);
	if (ret > 0)
		print_choice(get_cont()->l);
	return (0);
}
