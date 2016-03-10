/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_up_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:48:16 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 11:50:09 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"
#include "read_line.h"
#include "events.h"

void	moveup(t_line *l)
{
	int		len;
	int		rowsav;
	int		colsav;

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

void	movedown(t_line *l)
{
	int		len;
	int		rowsav;
	int		colsav;

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

void	moveupdown(t_line *l, int move)
{
	if (move == K_ALTUP)
		moveup(l);
	else if (move == K_ALTDWN)
		movedown(l);
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
