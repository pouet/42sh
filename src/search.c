/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 08:23:57 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/27 10:00:48 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "libft.h"
#include "search.h"
#include "events.h"
#include "context.h"

void	find_search(t_context *cont, int len)
{
	t_node			*n;
	int				ncur;

	n = cont->l->first;
	ncur = 0;
	while (n && ft_strncmp(cont->srch.word, ((t_choice *)n->data)->name, len))
	{
		n = n->next;
		ncur++;
	}
	cont->srch.found = 0;
	if (n)
	{
		cont->cur = n;
		cont->ncur = ncur;
		cont->srch.found = 1;
	}
}

void	search(t_context *cont, t_events *ev)
{
	time_t			now;
	int				len;

	if (ev->type != T_ALPHA)
		return ;
	now = clock();
	if (now - cont->srch.old >= CLOCKS_PER_SEC / 2 + CLOCKS_PER_SEC / 4)
		cont->srch.word[0] = '\0';
	len = ft_strlen(cont->srch.word);
	if (len < BUFF_SZ - 1)
	{
		cont->srch.old = now;
		cont->srch.word[len++] = ev->c;
		cont->srch.word[len] = '\0';
	}
	find_search(cont, len);
}
