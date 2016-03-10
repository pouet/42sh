/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:55:05 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 12:02:13 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "read_line.h"
#include "move.h"
#include "history.h"
#include "clipboard.h"
#include "events.h"
#include "completion.h"
#include "addchar.h"

void	clipboard_key(t_line *l, int move)
{
	int		i;

	if (move == K_ALTA)
		clip_cut(C_CUTBEG, l);
	else if (move == K_ALTS)
		clip_cut(C_CUTEND, l);
	else if (move == K_ALTD)
		clip_cut(C_CUTALL, l);
	else if (move == K_ALTZ)
		clip_copy(C_CPYBEG, l);
	else if (move == K_ALTX)
		clip_copy(C_CPYEND, l);
	else if (move == K_ALTC)
		clip_copy(C_CPYALL, l);
	else if (move == K_ALTV)
		clip_paste(l);
	i = l->i;
	l->i = 0;
	l->currow = 0;
	l->curcol = l->lenprompt;
	while (l->i < i)
		movelr(l, K_RIGHT);
}

void	histo_key(t_history *h, t_line *l, int move)
{
	if (h == NULL)
		return ;
	if (move == K_UP)
		histo_up(h, l);
	else if (move == K_DOWN)
		histo_down(h, l);
	l->i = 0;
	l->curcol = l->lenprompt;
	l->currow = 0;
	while (l->i < l->len)
		movelr(l, K_RIGHT);
}

int		key(t_line *l, t_history *h, t_events *ev)
{
	if (ev->type != T_KEYS)
		return (0);
	if (ev->c == K_LEFT || ev->c == K_RIGHT)
		movelr(l, ev->c);
	else if (ev->c == K_ALTUP || ev->c == K_ALTDWN)
		moveupdown(l, ev->c);
	else if (ev->c == K_ALTLFT || ev->c == K_ALTRGT)
		moveword(l, ev->c);
	else if (ev->c == K_DEL || ev->c == K_BCKSP)
		delchar(l, ev->c);
	else if (ev->c == K_HOME || ev->c == K_END)
		move_homeend(l, ev->c);
	else if (ev->c == K_UP || ev->c == K_DOWN)
		histo_key(h, l, ev->c);
	else if (ev->c == K_ALTA || ev->c == K_ALTS || ev->c == K_ALTD ||
			ev->c == K_ALTZ || ev->c == K_ALTX || ev->c == K_ALTC ||
			ev->c == K_ALTV)
		clipboard_key(l, ev->c);
	else if (ev->c == K_CTRLD)
	{
		free(l->s);
		l->s = NULL;
		return (1);
	}
	return (0);
}

void	tabulation(t_line *l, t_env *env, t_events *ev, char *prompt)
{
	if (ev->type == T_ALPHA && ev->c == '\t')
	{
		if (completion(l, env))
		{
			ft_putstr(prompt);
			ft_putstr(l->s);
			movecur_backtoi(l);
		}
	}
}

int		character(t_line *l, t_events *ev)
{
	if (ev->type == T_ALPHA && ev->c != '\t')
	{
		add_char(l, ev->c);
		if (ev->c == '\n')
			return (1);
	}
	return (0);
}
