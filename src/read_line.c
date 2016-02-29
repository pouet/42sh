/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 10:15:28 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/26 16:42:41 by nchrupal         ###   ########.fr       */
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

void	print_line(t_line *l, char *prompt);
void	movecurlr(t_line *l, int move);

void	movelr_nl(t_line *l, int move)
{
	char	*t;
	int		i;
	int		tmp;

	if (move == K_LEFT && l->i > 0 && l->s[l->i] == '\n')
	{
		ft_tputs("cr");
		ft_tputs("up");
		t = ft_strchr(l->s, '\n');
		if (t != NULL && l->i <= t - l->s)
		{
			i = 0;
			while (i < l->lenprompt)
			{
				ft_tputs("nd");
				i++;
			}
		}
		i = l->i - 1;
		while (i > 0 && l->s[i] != '\n')
			i--;
		if (i != l->i - 1 && l->s[i] == '\n')
			i++;
		tmp = l->i;
		l->i = i;
//		eprintf("%d\n", tmp-i);
		while (tmp - i > 0)
		{
			if (l->s[l->i] == '\n')
			{
				ft_tputs("nd");
				l->i++;
			}
			else
				movecurlr(l, K_RIGHT);
			i++;
//			ft_tputs("nd");
//			i++;
		}
			ft_tputs("nd");
	}
	else if (move == K_RIGHT && l->i < l->len)
	{
	}
}

void	movecurlr(t_line *l, int move)
{
	int		i;

	if (move == K_LEFT && l->i > 0)
	{
		if (l->row > 0)
			mv_cur("UP", 0, l->row);
		ft_tputs("cr");
		mv_cur("DO", 0, l->currow);
		mv_cur("RI", l->curcol, 0);

/*		l->i--;
		l->curcol--;
//		if (l->s[l->i] == '\n')
//			printf("[%d-%d]", l->i, l->curcol);
		if (l->curcol < 0)
		{
			printf("[%d-%d]", l->i, l->curcol);
			l->currow--;
			l->curcol = 0;
			if (l->currow == 0)
				l->curcol = l->lenprompt;
//		ft_tputs("cr");
//		ft_tputs("up");
			i = l->i - 1;
			while (i > 0 && l->s[i] != '\n')
			{
				i--;
				l->curcol++;
//			ft_tputs("le");
			}
			printf("[%d-%d]", l->i, l->curcol);
//			movelr_nl(l, move);
			ft_tputs("cr");
			ft_tputs("up");
			mv_cur("RI", l->curcol, 0);
		}
		else
			ft_tputs("le");*/
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
	int		i;

	if (move == K_LEFT && l->i > 0)
	{
		l->i--;
		l->curcol--;
		if (l->curcol < 0)
		{
			l->currow--;
			l->curcol = 0;
			if (l->currow == 0)
				l->curcol = l->lenprompt;
			i = l->i;
			/* TODO: indice de '\n' sans le -1 */
			while (i > 0 && l->curcol < l->wincol - 1 && l->s[i] != '\n')
			{
				i--;
				l->curcol++;
			}
		}
	}
	else if (move == K_RIGHT && l->i < l->len)
	{
		l->i++;
		l->curcol++;
		if (l->curcol >= l->wincol || (l->i < l->len && l->s[l->i] == '\n'))
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
//	printf("[%d-%d-%d-%d]", l->row, l->col, l->currow, l->curcol);
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
//	mv_cur("RI", 0, l->lenprompt);
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
	int		i;
	int		len;
	int		rowsav;
	int		colsav;

	if (move == K_ALTUP)
	{
		rowsav = l->currow;
		colsav = l->curcol;
		while (l->i > 0 && l->currow > rowsav - 2)
			movelr(l, K_LEFT);
		movelr(l, K_RIGHT);
		if (l->s[l->i] == '\n')
			movelr(l, K_RIGHT);
		printf("%d-", l->i);
		if (l->currow == rowsav - 1)
		{
			len = l->i + colsav;
			printf("%d-", len);
			while (l->i < l->len && l->s[l->i] != '\n' && len > 0)
			{
				movelr(l, K_RIGHT);
				len--;
			}
		}
/*		i = l->i;
		if (l->s[i] == '\n')
			i--;
		while (i > 0 && l->s[i] != '\n')
			i--;
		len = i;
		if (i > 0 && l->s[i] == '\n')
			i--;
		while (i > 0 && l->s[i] != '\n')
			i--;
		if (l->s[i] == '\n')
			i++;
		printf("[%d-%d]", i, len);
		if (i + l->col > len)
			i = len;
		else
			i = i + l->col;
		printf("%d-", i);
		while (l->i > i)
			movelr(l, K_LEFT);*/




/*		len = 0;
		i = l->i - (l->col + 1);
		if (i < 0)
			i = 0;
		if (l->s[i] == '\n')
		{
			len = i;
			i--;
		}
		while (i > 0 && l->s[i] != '\n')
			i--;
		if (l->s[i] == '\n')
			i++;
		if (i + l->col >= len)
			i = len;
		else
			i += l->col;
		if ((l->i - (l->col + 1)) < i + l->col)
			len = l->col + 1;
		else
			len = ((l->i - (l->col + 1) - 0) - i) + l->col + 0;
		printf("[%d-%d-%c-%d-%d]", l->i, i, l->s[i], len, l->col);
		i = l->i - i;
		while (i < len)
		{
			movelr(l, K_LEFT);
			i++;
		}
//		if (l->s[l->i] == '\n')
//			l->i--;
//		i = 0;
//		while (l->i > 0 && i < l->wincol && l->s[l->i] != '\n')
		{
//			movelr(l, K_LEFT);
//			i++;
		}*/
	}
	else if (move == K_ALTDWN)
	{
		if (l->s[l->i] == '\n')
			l->i++;
		i = 0;
		while (l->i < l->len && i < l->wincol && l->s[l->i] != '\n')
		{
			movelr(l, K_RIGHT);
			i++;
		}
		if (l->s[l->i] == '\n')
			movelr(l, K_RIGHT);
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
		if (l->s[l->i] == ' ' && l->i != 0)
			movelr(l, K_RIGHT);
	}
	else if (move == K_ALTRGT && l->i < l->len)
	{
		while (l->i < l->len && l->s[l->i] != ' ')
			movelr(l, K_RIGHT);
		while (l->i < l->len && l->s[l->i] == ' ')
			movelr(l, K_RIGHT);
		if (l->s[l->i] == ' ' && l->i != l->len)
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
	/* TODO: maj des coordonnees 'cur' */
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

char	*read_line(char *prompt, t_history *h)
{
	t_line			*l;
	int				ret;
	t_events		ev;
//	struct winsize	ws;

	ft_tputs("sc");
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
				ft_putendl("");
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
				/* free t_line */
				return (NULL);
			}
			print_line(l, prompt);
		}
	}
	return (linetos(l));
}
