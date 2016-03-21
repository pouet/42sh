/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 17:56:17 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/21 18:58:17 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "read_line.h"
#include "histo_search.h"
#include "events.h"
#include "addchar.h"

void		replace_str(t_line *l, char *s)
{
	int				i;

	while (l->i > 0)
		delchar(l, K_BCKSP);
	while (l->len > 0)
		delchar(l, K_DEL);
	i = 0;
	while (s[i] != '\0')
		add_char(l, s[i++]);
}

void		histo_search(t_line *l, t_history *h, t_events *ev)
{
	static t_node	*dll;
	static char		s[BUFF_SZ + 1];
	static int		len;

	if (ev->type == T_KEYS && ev->c == K_CTRLR && l->len > 0)
	{
		if (dll == NULL)
		{
			ft_strcpy(s, l->s);
			len = l->len;
			dll = h->dll->first;
		}
		else
			dll = dll->next;
		while (dll != NULL && ft_strncmp(s, dll->data, len) != 0)
			dll = dll->next;
		if (dll != NULL && ft_strncmp(s, dll->data, len) == 0)
			replace_str(l, dll->data);
	}
	else
		dll = NULL;
}
