/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 10:15:28 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/01 09:14:45 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <term.h>
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
	char	*s;

	s = l->s;
	free(l);
	return (s);
}

void	print_char(char c)
{
	ft_tputs("im");
	ft_tputs("ic");
	ft_putchar(c);
	ft_tputs("ip");
	ft_tputs("ei");
}

void	movecurlr(t_line *l, int move)
{
	if (move == K_LEFT && l->i > 0)
	{
		if (l->row > 0)
			mv_cur("UP", 0, l->row);
		ft_tputs("cr");
		if (l->currow > 0)
			mv_cur("DO", 0, l->currow);
		if (l->curcol > 0)
			mv_cur("RI", l->curcol, 0);
	}
	else if (move == K_RIGHT && l->i < l->len)
	{
		l->i++;
		if ((l->i + l->lenprompt) % l->wincol == 0 ||
			(l->i > 0 && l->s[l->i - 1] == '\n'))
		{
			ft_tputs("do");
			ft_tputs("cr");
		}
		else
			ft_tputs("nd");
	}
}

void	movelr(t_line *l, int move)
{
	int		len;

	if (move == K_LEFT && l->i > 0)
	{
		l->i--;
		l->curcol--;
		if (l->curcol < 0)
		{
			len = l->i;
			l->i = 0;
			l->currow = 0;
			l->curcol = l->lenprompt;
			while (l->i < len)
				movelr(l, K_RIGHT);
		}
	}
	else if (move == K_RIGHT && l->i < l->len)
	{
		l->i++;
		l->curcol++;
		if (l->curcol >= l->wincol ||
			(l->i < l->len && l->s[l->i - 1] == '\n'))
		{
			l->currow++;
			l->curcol = 0;
		}
	}
}

void	clrscr_down(t_line *l)
{
	if (l->currow > 0)
		mv_cur("UP", 0, l->currow);
	ft_tputs("cr");
	ft_tputs("cd");
}

void	movecur_backtoi(t_line *l)
{
	ft_tputs("cr");
	if (l->row > 0)
		mv_cur("UP", 0, l->row);
	if (l->currow > 0)
		mv_cur("DO", 0, l->currow);
	if (l->curcol > 0)
		mv_cur("RI", 0, l->curcol);
}

void	putprompt_lastline(char *prompt)
{
	int		len;

	len = ft_strlen(prompt);
	while (len > 0 && prompt[len] != '\n')
		len--;
	if (prompt[len] == '\n')
		len++;
	ft_putstr(prompt + len);
}

void	print_line(t_line *l, char *prompt)
{
	int		i;

	l->oldrow = l->row;
	l->oldcol = l->col;
	putprompt_lastline(prompt);
	l->col = l->lenprompt;
	l->row = 0;
	i = 0;
	while (i < l->len)
	{
		ft_putchar(l->s[i]);
		if (l->s[i] == '\n')
		{
			l->row++;
			l->col = 0;
		}
		else
			l->col++;
		if (l->col >= l->wincol)
		{
			l->row++;
			l->col = 0;
		}
		i++;
	}
	if (l->col == 0)
		ft_putchar(' ');
	movecur_backtoi(l);
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
	l->s[l->i] = c;
	l->i++;
	l->len++;
	l->s[l->len] = '\0';
	l->curcol++;
	if (l->curcol >= l->wincol)
	{
		l->curcol = 0;
		l->currow++;
	}
	return (l->s);
}

void	moveupdown(t_line *l, int move)
{
	int		len;
	int		rowsav;
	int		colsav;

	if (move == K_ALTUP)
	{
		rowsav = l->currow;
		colsav = l->curcol;
		while (l->i > 0 && l->curcol > 0)
			movelr(l, K_LEFT);
		movelr(l, K_LEFT);
		while (l->i > 0 && l->curcol > 0)
			movelr(l, K_LEFT);
		if (l->currow != rowsav)
		{
			len = colsav;
			if (l->currow == 0)
				len -= l->lenprompt;
			while (l->i < l->len && l->s[l->i] != '\n' && len > 0)
			{
				movelr(l, K_RIGHT);
				len--;
			}
		}
	}
	else if (move == K_ALTDWN)
	{
		rowsav = l->currow;
		colsav = l->curcol;
		while (l->i < l->len && l->curcol != 0)
			movelr(l, K_RIGHT);
		len = colsav;
		while (l->i < l->len && l->s[l->i] != '\n' && len > 0)
		{
			movelr(l, K_RIGHT);
			len--;
		}
	}
}

void	moveword(t_line *l, int move)
{
	if (move == K_ALTLFT && l->i > 0)
	{
		while (l->i > 0 && !ft_isalnum(l->s[l->i - 1]))
			movelr(l, K_LEFT);
		while (l->i > 0 && ft_isalnum(l->s[l->i - 1]))
			movelr(l, K_LEFT);
		if (!ft_isalnum(l->s[l->i]) && l->i != 0)
			movelr(l, K_RIGHT);
	}
	else if (move == K_ALTRGT && l->i < l->len)
	{
		while (l->i < l->len && ft_isalnum(l->s[l->i]))
			movelr(l, K_RIGHT);
		while (l->i < l->len && !ft_isalnum(l->s[l->i]))
			movelr(l, K_RIGHT);
		if (!ft_isalnum(l->s[l->i]) && l->i != l->len)
			movelr(l, K_LEFT);
	}
}

void	delchar(t_line *l, int move)
{
	if (move == K_BCKSP && l->i > 0)
	{
		ft_memmove(l->s + l->i - 1, l->s + l->i, l->len - l->i);
		movelr(l, K_LEFT);
		l->len--;
		l->s[l->len] = '\0';
	}
	else if (move == K_DEL && l->i < l->len)
	{
		ft_memmove(l->s + l->i, l->s + l->i + 1, l->len - l->i);
		l->len--;
		l->s[l->len] = '\0';
	}
}

void	move_homeend(t_line *l, int move)
{
	if (move == K_HOME)
	{
		while (l->i > 0)
			movelr(l, K_LEFT);
	}
	else if (move == K_END)
	{
		while (l->i < l->len)
			movelr(l, K_RIGHT);
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
	i = l->i;
	l->i = 0;
	l->currow = 0;
	l->curcol = l->lenprompt;
	while (l->i < i)
		movelr(l, K_RIGHT);
}

int		lenprompt(char *prompt)
{
	int		len;
	int		i;
	char	*s;
	char	*t;

	len = ft_strlen(prompt);
	i = len - 1;
	while (i > 0 && prompt[i] != '\n')
		i--;
	prompt += i;
	if (*prompt == '\n')
		prompt++;
	i = 0;
	len = ft_strlen(prompt);
	while (prompt[i])
	{
		if ((s = ft_strchr(prompt + i, '\e')) != NULL &&
			(t = ft_strchr(s + 1, 'm')) != NULL)
		{
			prompt = t + 1;
			len -= t - s + 1;
		}
		i++;
	}
	return (len);
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

#include <sys/ioctl.h>
#include <signal.h>
static int	g_sigint_line;

void	sigint_line(int sig)
{
	char	c;

	(void)sig;
	c = '\n';
	g_sigint_line = 1;
	ioctl(0, TIOCSTI, &c);
	signal(SIGINT, SIG_IGN);
}

char	*read_line(char *prompt, t_history *h)
{
	t_line			*l;
	int				ret;
	t_events		ev;
//	int				i;
//	struct winsize	ws;

	signal(SIGINT, sigint_line);
	g_sigint_line = 0;

//	ft_tputs("sc");
	ft_putstr(prompt);
	l = new_line();
	l->lenprompt = lenprompt(prompt);
	l->col = l->lenprompt;
	l->row = 0;
	l->oldcol = l->col;
	l->oldrow = l->row;
	l->curcol = l->col;
	l->currow = l->row;
	while ((ret = getevents(&ev)) > 0/* || (ret == 0 && ev.c == '\n')*/)
	{
		if (g_sigint_line != 0)
		{
			/* TODO: a refaire pour le multiligne avec guillemets... */
			l->s[0] = '\0';
			break ;
		}
//		ioctl(0, TIOCGWINSZ, &ws);
//		l->col = ws.ws_col;
//		l->lig = ws.ws_row;
		l->wincol = tgetnum("co");
		l->winrow = tgetnum("li");
		clrscr_down(l);
		if (ev.type == T_ALPHA)
		{
			add_char(l, ev.c);
			print_line(l, prompt);
//			print_char(ev.c);
			if (ev.c == '\n')
			{
//				i = 0;
//				while (i < l->row)
//				{
//					ft_putendl("");
//					i++;
//				}
				break ;
			}
		}
		else
		{
			if (ev.c == K_LEFT || ev.c == K_RIGHT)
				movelr(l, ev.c);
			else if (ev.c == K_ALTUP || ev.c == K_ALTDWN)
				moveupdown(l, ev.c);
			else if (ev.c == K_ALTLFT || ev.c == K_ALTRGT)
				moveword(l, ev.c);
			else if (ev.c == K_DEL || ev.c == K_BCKSP)
				delchar(l, ev.c);
			else if (ev.c == K_HOME || ev.c == K_END)
				move_homeend(l, ev.c);
			else if (ev.c == K_UP || ev.c == K_DOWN)
				histo_key(h, l, ev.c);
			else if (ev.c == K_ALTA || ev.c == K_ALTS || ev.c == K_ALTD ||
					ev.c == K_ALTZ || ev.c == K_ALTX || ev.c == K_ALTC ||
					ev.c == K_ALTV)
				clipboard_key(l, ev.c);
			else if (ev.c == K_CTRLD)
			{
				free(l->s);
				l->s = NULL;
				break ;
				/* free t_line */
//				return (NULL);
			}
			print_line(l, prompt);
		}
	}
	signal(SIGINT, SIG_IGN);
	ft_putendl("");
	return (linetos(l));
}
