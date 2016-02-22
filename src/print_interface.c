/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 12:39:57 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/27 08:57:44 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_interface.h"
#include "colors.h"
#include "print.h"

void	print_edge(t_context *cont)
{
	int		i;

	i = 0;
	while (i < cont->ws.ws_row)
	{
		mv_cur(0, i);
		col_putstr_tty(" ", NULL, NULL, BAKCYN);
		mv_cur(cont->ws.ws_col - 1, i);
		col_putstr_tty(" ", NULL, NULL, BAKCYN);
		i++;
	}
	i = 0;
	while (i < cont->ws.ws_col)
	{
		mv_cur(i, 0);
		col_putstr_tty(" ", NULL, NULL, BAKCYN);
		mv_cur(i, cont->ws.ws_row - 1);
		col_putstr_tty(" ", NULL, NULL, BAKCYN);
		i++;
	}
	if (cont->co >= 9)
	{
		mv_cur((cont->ws.ws_col / 2) - 4, 0);
		col_putstr_tty("ft_select", TXTBLK, NULL, BAKCYN);
	}
}

void	print_search(t_context *cont)
{
	int		i;

	i = 0;
	if ((unsigned)cont->co > ft_strlen(cont->srch.word) + 7 + 2 &&
			cont->srch.found >= 0)
	{
		mv_cur(2, cont->ws.ws_row - 1);
		col_putstr_tty("search: ", TXTBLK, NULL, BAKCYN);
		if (cont->srch.found == 0)
			col_putstr_tty(cont->srch.word, TXTBLK, NULL, BAKRED);
		else
			col_putstr_tty(cont->srch.word, TXTBLK, NULL, BAKCYN);
	}
}

void	print_cmd(t_context *cont)
{
	int		i;

	i = 0;
	while (i < cont->co)
	{
		mv_cur(i + 1, 1);
		col_putstr_tty(" ", NULL, NULL, BAKGRN);
		i++;
	}
	if (cont->co >= 70)
	{
		mv_cur((cont->co / 2) - 35 + 1, 1);
		col_putstr_tty("ARROWS: move | SPACE: select | ENTER: choose | ",
				TXTBLK, NULL, BAKGRN);
		col_putstr_tty("DEL: delete | ESC: quit", TXTBLK, NULL, BAKGRN);
	}
}

t_node	*print_arrows(t_context *cont, int maxco)
{
	t_node		*n;
	int			tmp;
	int			sz;

	n = cont->l->first;
	sz = cont->ncur / cont->li;
	if (sz >= maxco)
	{
		tmp = (sz - (sz % maxco)) * cont->li;
		while (n && tmp > 0)
		{
			n = n->next;
			tmp--;
		}
		mv_cur(0, cont->ws.ws_row / 2);
		col_putstr_tty("<", TXTBLK, NULL, BAKRED);
	}
	sz = (cont->l->sz - 1) / cont->li;
	tmp = (sz - (sz % maxco)) * cont->li;
	if (tmp > cont->ncur)
	{
		mv_cur(cont->ws.ws_col - 1, cont->ws.ws_row / 2);
		col_putstr_tty(">", TXTBLK, NULL, BAKRED);
	}
	return (n);
}
