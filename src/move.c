/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:44:21 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 14:31:27 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"
#include "events.h"
#include "print.h"
#include "read_line.h"

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
		if (--l->curcol < 0)
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
		if (l->curcol >= l->wincol || (l->i < l->len && l->s[l->i - 1] == '\n'))
		{
			l->currow++;
			l->curcol = 0;
		}
	}
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

void	movecur_last(t_line *l)
{
	if (l->currow > 0)
		mv_cur("UP", 0, l->currow);
	ft_tputs("cr");
	if (l->row > 0)
		mv_cur("DO", 0, l->row);
	if (l->col > 0)
		mv_cur("RI", 0, l->col);
	ft_putendl("");
}
