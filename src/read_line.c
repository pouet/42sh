/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 10:15:28 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/23 15:49:49 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "read_line.h"
#include "lexer.h"
#include "error.h"
#include "events.h"
#include "xmalloc.h"
#include "print.h"

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

char	*add_char(t_line *l, char c)
{
	char		*tmp;

	if (c == '\n')
		return (l->s);
	if (l->len + 1 >= l->lenmax)
	{
		puts("c'est ca...");
		l->lenmax += BUFF_SZ;
		tmp = xmalloc((l->lenmax + 1) * sizeof(*l->s));
		ft_bzero(l->s, l->lenmax + 1);
		ft_strcpy(tmp, l->s);
		free(l->s);
		l->s = tmp;
	}
	ft_memmove(l->s + l->i + 1, l->s + l->i, l->len - l->i);
//	ft_strcpy(l->s + l->i, l->s + l->i + 1);
	l->s[l->i] = c;
	l->i++;
	l->len++;
	l->s[l->len] = '\0';
	return (l->s);
}

void	movelr(t_line *l, int move)
{
	if (move == K_LEFT && l->i > 0)
	{
		l->i--;
		ft_tputs("le");
	}
	else if (move == K_RIGHT && l->i < l->len)
	{
		l->i++;
		ft_tputs("nd");
	}
}

void	delchar(t_line *l, int move)
{
	ft_tputs("dm");
	if (move == K_BCKSP && l->i > 0)
	{
		ft_tputs("le");
		ft_tputs("dc");
		ft_memmove(l->s + l->i - 1, l->s + l->i, l->len - l->i);
		l->i--;
		l->len--;
		l->s[l->len] = '\0';
	}
	else if (move == K_DEL && l->i < l->len)
	{
		ft_tputs("dc");
		ft_memmove(l->s + l->i, l->s + l->i + 1, l->len - l->i);
		l->len--;
		l->s[l->len] = '\0';
	}
	ft_tputs("ed");
}

char	*read_line(int history)
{
	t_line		*l;
	int			ret;
	t_events	ev;

	(void)history;

	l = new_line();
	while ((ret = getevents(&ev)) > 0/* || (ret == 0 && ev.c == '\n')*/)
	{
		if (ev.type == T_ALPHA)
		{
			add_char(l, ev.c);
			print_char(ev.c);
			if (ev.c == '\n')
				break ;
		}
		else
		{
			if (ev.c == K_LEFT || ev.c == K_RIGHT)
				movelr(l, ev.c);
			else if (ev.c == K_DEL || ev.c == K_BCKSP)
				delchar(l, ev.c);
			else if (ev.c == K_CTRLD)
			{
				/* free t_line */
				return (NULL);
			}
		}
	}
	return (linetos(l));
}
