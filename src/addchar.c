/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:59:49 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 12:17:29 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"
#include "libft.h"
#include "events.h"
#include "addchar.h"
#include "move.h"

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
