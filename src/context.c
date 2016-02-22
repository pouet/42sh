/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 09:04:21 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/26 10:49:14 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <term.h>
#include "libft.h"
#include "dll.h"
#include "context.h"

int		init_context(t_context *cont, int ac, char **av)
{
	int			i;
	t_node		*n;
	t_choice	c;

	cont->l = dll_newlist();
	i = 1;
	while (i < ac)
	{
		c.len = ft_strlen(av[i]);
		ft_strncpy(c.name, av[i], BUFF_SZ);
		c.select = 0;
		if ((n = dll_createnode(&c, sizeof(c))) == NULL)
			return (-1);
		dll_pushback(cont->l, n);
		i++;
	}
	cont->cur = cont->l->first;
	cont->ncur = 0;
	cont->nprev = 0;
	cont->li = tgetnum("li");
	cont->co = tgetnum("co");
	cont->srch.word[0] = '\0';
	cont->srch.old = clock();
	cont->srch.found = -1;
	return (0);
}

void	selchoice(t_context *cont)
{
	t_choice *c;

	c = cont->cur->data;
	c->select = !c->select;
	cont->cur = dll_move(cont->l, cont->cur, 1, &cont->ncur);
}

void	delchoice(t_context *cont)
{
	t_node	*n;
	int		tmp;

	tmp = cont->ncur;
	if (cont->cur->next == NULL)
	{
		n = cont->cur->prev;
		tmp--;
	}
	else
		n = cont->cur->next;
	dll_delnode(cont->l, cont->ncur);
	cont->ncur = tmp;
	cont->nprev = tmp;
	cont->cur = n;
}
