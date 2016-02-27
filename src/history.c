/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 14:25:01 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/26 08:42:49 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "history.h"
#include "libft.h"
#include "xmalloc.h"
#include "read_line.h"
#include "print.h"

void	histo_load(t_history *h)
{
	/* TODO: charger le fichier */
	h->dll = dll_newlist();
	h->new = dll_createnode("", 1);
	h->cur = h->new;
}

int		histo_add(t_history *h, char *s)
{
	int		len;

	len = ft_strlen(s);
	if (len > 0)
		dll_pushfront(h->dll, dll_createnode(s, len + 1));
	h->cur = h->new;
	((char*)(h->new->data))[0] = '\0';
	return (0);
}

int		histo_up(t_history *h, t_line *l)
{
	int		len;

	if (h->cur == h->new && h->dll->sz > 0)
	{
		free(h->new->data);
		h->new->data = ft_strdup(l->s);
		h->cur = h->dll->first;
	}
	else if (h->cur->next != NULL)
		h->cur = h->cur->next;
	else
		return (0);
	len = ft_strlen(h->cur->data);
	if (len >= l->lenmax)
		l = growup_line(l);
	ft_strcpy(l->s, h->cur->data);
	l->len = len;
	l->i = len;
	return (1);
}

int		histo_down(t_history *h, t_line *l)
{
	int		len;

	if (h->cur == h->dll->first)
		h->cur = h->new;
	else if (h->cur->prev != NULL)
		h->cur = h->cur->prev;
	else
		return (0);
	len = ft_strlen(h->cur->data);
	if (len >= l->lenmax)
		l = growup_line(l);
	ft_strcpy(l->s, h->cur->data);
	l->len = len;
	l->i = len;
	return (1);
}
