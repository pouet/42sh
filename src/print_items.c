/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 12:00:06 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/27 09:04:32 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "print_items.h"
#include "dll.h"
#include "colors.h"
#include "print.h"
#include "print_interface.h"
#include "tty.h"

void	setcolor_byext(char *name)
{
	int		len;

	len = ft_strlen(name);
	if (len >= 2 && ft_strncmp(name + (len - 2), ".c", 2) == 0)
		ft_putstr_fd(TXTPUR, get_tty_fd());
	if (len >= 2 && ft_strncmp(name + (len - 2), ".h", 2) == 0)
		ft_putstr_fd(BLDGRN, get_tty_fd());
	if (len >= 3 && (ft_strncmp(name + (len - 3), ".sh", 3) == 0 ||
			ft_strncmp(name + (len - 3), ".pl", 3) == 0))
		ft_putstr_fd(TXTRED, get_tty_fd());
	if (len >= 4 && (ft_strncmp(name + (len - 4), ".jpg", 4) == 0 ||
			ft_strncmp(name + (len - 4), ".png", 4) == 0))
		ft_putstr_fd(TXTCYN, get_tty_fd());
	if (len >= 4 && (ft_strncmp(name + (len - 4), ".pdf", 4) == 0 ||
			ft_strncmp(name + (len - 4), ".zip", 4) == 0))
		ft_putstr_fd(TXTGRN, get_tty_fd());
}

void	print_one(t_context *cont, t_node *n, int co, int li)
{
	unsigned	flags;
	t_choice	*c;

	c = n->data;
	setcolor_byext(c->name);
	flags = TXT_NORM;
	if (n == cont->cur)
		flags |= TXT_UDRL;
	if (c->select)
		flags |= TXT_RVID;
	print_txt(c->name, co + 2, li + 2, flags);
	ft_putstr_fd(TXTRST, get_tty_fd());
}

void	print_items(t_context *cont)
{
	t_node		*n;
	int			li;
	int			co;
	int			maxco;
	int			maxlen;

	maxlen = max_len(cont->l);
	maxco = (cont->co - 2) / maxlen;
	maxlen += ((cont->co - 2) / maxco) - maxlen + 1;
	li = 0;
	co = 0;
	n = print_arrows(cont, maxco);
	while (n && co < maxco)
	{
		print_one(cont, n, co * maxlen, li);
		n = n->next;
		li++;
		if (li >= cont->li)
		{
			li = 0;
			co++;
		}
	}
}

void	print_cont(t_context *cont)
{
	clr_screen();
	if (cont->ws.ws_row < 4 || cont->ws.ws_col < 4 + max_len(cont->l))
	{
		print_txt("window too small", 0, 0, TXT_NORM);
	}
	else if (cont->l->sz > 0)
	{
		print_edge(cont);
		print_search(cont);
		print_cmd(cont);
		print_items(cont);
	}
}

void	print_choice(t_dllist *l)
{
	t_node		*n;
	t_choice	*c;
	int			i;

	clr_screen();
	i = 0;
	n = l->first;
	while (n != NULL)
	{
		c = n->data;
		if (c->select)
		{
			if (i)
				ft_putchar(' ');
			i = 1;
			ft_putstr(c->name);
		}
		n = n->next;
	}
}
