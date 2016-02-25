/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 10:15:28 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/25 11:45:41 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "read_line.h"
#include "lexer.h"
#include "error.h"
#include "events.h"
#include "xmalloc.h"
#include "print.h"
#include "history.h"
#include "clipboard.h"

t_line	*new_line(void)
{
	t_line	*l;

	l = xmalloc(sizeof(*l));
	l->i = 0;
	l->len = 0;
	l->lenmax = BUFF_SZ;
	l->s = xmalloc((l->lenmax + 1) * sizeof(*l->s));
	ft_bzero(l->s, l->lenmax + 1);
	return (l);
}

char	*linetos(t_line *l)
{
	return (l->s);
}

void	print_char(char c)
{
	ft_tputs("im");
	ft_tputs("ic");
	ft_putchar(c);
	ft_tputs("ip");
	ft_tputs("ei");
}

t_line	*growup_line(t_line *l)
{
	char		*tmp;

	l->lenmax += BUFF_SZ;
	tmp = xmalloc((l->lenmax + 1) * sizeof(*l->s));
	ft_bzero(l->s, l->lenmax + 1);
	ft_strcpy(tmp, l->s);
	free(l->s);
	l->s = tmp;
	return (l);
}

char	*add_char(t_line *l, char c)
{

	if (c == '\n')
		return (l->s);
	if (l->len + 1 >= l->lenmax)
		l = growup_line(l);
	ft_memmove(l->s + l->i + 1, l->s + l->i, l->len - l->i);
//	ft_strcpy(l->s + l->i, l->s + l->i + 1);
	l->s[l->i] = c;
	l->i++;
	l->len++;
	l->s[l->len] = '\0';
	return (l->s);
}

void	movelr(t_line *l, int move)
{
	if (move == K_LEFT && l->i > 0)
	{
		l->i--;
		ft_tputs("le");
	}
	else if (move == K_RIGHT && l->i < l->len)
	{
		l->i++;
		ft_tputs("nd");
	}
}

void	moveword(t_line *l, int move)
{
	if (move == K_ALTLFT && l->i > 0)
	{
		while (l->i > 0 && l->s[l->i - 1] == ' ')
			movelr(l, K_LEFT);
		while (l->i > 0 && l->s[l->i - 1] != ' ')
			movelr(l, K_LEFT);
		if (l->s[l->i] == ' ')
			movelr(l, K_RIGHT);
	}
	else if (move == K_ALTRGT && l->i < l->len)
	{
		while (l->i < l->len && l->s[l->i] != ' ')
			movelr(l, K_RIGHT);
		while (l->i < l->len && l->s[l->i] == ' ')
			movelr(l, K_RIGHT);
		if (l->s[l->i] == ' ')
			movelr(l, K_LEFT);
	}
}

void	delchar(t_line *l, int move)
{
	ft_tputs("dm");
	if (move == K_BCKSP && l->i > 0)
	{
		ft_tputs("le");
		ft_tputs("dc");
		ft_memmove(l->s + l->i - 1, l->s + l->i, l->len - l->i);
		l->i--;
		l->len--;
		l->s[l->len] = '\0';
	}
	else if (move == K_DEL && l->i < l->len)
	{
		ft_tputs("dc");
		ft_memmove(l->s + l->i, l->s + l->i + 1, l->len - l->i);
		l->len--;
		l->s[l->len] = '\0';
	}
	ft_tputs("ed");
}

void	move_homeend(t_line *l, int move)
{
	int		i;

	ft_tputs("rc");
	if (move == K_HOME)
	{
		l->i = 0;
	}
	else if (move == K_END)
	{
		l->i = l->len;
		i = 0;
		while (i < l->len)
		{
			ft_tputs("nd");
			i++;
		}
	}
}

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
	ft_tputs("rc");
	ft_tputs("ce");
	ft_putstr(l->s);
	ft_tputs("rc");
	i = 0;
	while (i++ < l->i)
		ft_tputs("nd");
}

char	*read_line(t_history *h)
{
	t_line		*l;
	int			ret;
	t_events	ev;

	ft_tputs("sc");
	l = new_line();
	while ((ret = getevents(&ev)) > 0/* || (ret == 0 && ev.c == '\n')*/)
	{
		if (ev.type == T_ALPHA)
		{
			add_char(l, ev.c);
			print_char(ev.c);
			if (ev.c == '\n')
				break ;
		}
		else
		{
			if (ev.c == K_LEFT || ev.c == K_RIGHT)
				movelr(l, ev.c);
			else if (ev.c == K_ALTLFT || ev.c == K_ALTRGT)
				moveword(l, ev.c);
			else if (ev.c == K_DEL || ev.c == K_BCKSP)
				delchar(l, ev.c);
			else if (ev.c == K_HOME || ev.c == K_END)
				move_homeend(l, ev.c);
			else if (ev.c == K_UP)
				histo_up(h, l);
			else if (ev.c == K_DOWN)
				histo_down(h, l);
			else if (ev.c == K_ALTA || ev.c == K_ALTS || ev.c == K_ALTD ||
					ev.c == K_ALTZ || ev.c == K_ALTX || ev.c == K_ALTC ||
					ev.c == K_ALTV)
				clipboard_key(l, ev.c);
			else if (ev.c == K_CTRLD)
			{
				/* free t_line */
				return (NULL);
			}
		}
	}
	histo_add(h, l);
	return (linetos(l));
}
