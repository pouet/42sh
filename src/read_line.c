/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 10:15:28 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/21 18:45:53 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <term.h>
#include "libft.h"
#include "read_line.h"
#include "lexer.h"
#include "error.h"
#include "events.h"
#include "xmalloc.h"
#include "print.h"
#include "history.h"
#include "clipboard.h"
#include "completion.h"
#include "move.h"
#include "print_line.h"
#include "keys.h"
#include "addchar.h"
#include "histo_search.h"

t_line	*new_line(int lenp)
{
	t_line	*l;

	l = xmalloc(sizeof(*l));
	l->i = 0;
	l->len = 0;
	l->lenmax = BUFF_SZ;
	l->s = xmalloc((l->lenmax + 1) * sizeof(*l->s));
	ft_bzero(l->s, l->lenmax + 1);
	l->lenprompt = lenp;
	l->col = l->lenprompt;
	l->row = 0;
	l->oldcol = l->col;
	l->oldrow = l->row;
	l->curcol = l->col;
	l->currow = l->row;
	return (l);
}

char	*linetos(t_line *l)
{
	char	*s;

	s = l->s;
	free(l);
	return (s);
}

t_line	*growup_line(t_line *l)
{
	char		*tmp;

	l->lenmax += BUFF_SZ;
	tmp = xmalloc((l->lenmax + 1) * sizeof(*l->s));
	ft_bzero(tmp, l->lenmax + 1);
	ft_strcpy(tmp, l->s);
	free(l->s);
	l->s = tmp;
	return (l);
}

int		lenprompt(char *prompt)
{
	int		len;
	int		i;
	char	*s;
	char	*t;

	len = ft_strlen(prompt);
	i = len - 1;
	while (i > 0 && prompt[i] != '\n')
		i--;
	prompt += i;
	if (*prompt == '\n')
		prompt++;
	i = 0;
	len = ft_strlen(prompt);
	while (prompt[i])
	{
		if ((s = ft_strchr(prompt + i, '\x1b')) != NULL &&
			(t = ft_strchr(s + 1, 'm')) != NULL)
		{
			prompt = t + 1;
			len -= t - s + 1;
		}
		i++;
	}
	return (len);
}

char	*read_line(char *prompt, t_history *h, t_env *env, int *sig)
{
	t_line			*l;
	int				ret;
	t_events		ev;

	ft_putstr(prompt);
	l = new_line(lenprompt(prompt));
	while ((ret = getevents(&ev)) > 0)
	{
		l->wincol = tgetnum("co");
		l->winrow = tgetnum("li");
		tabulation(l, env, &ev, prompt);
		clrscr_down(l);
		histo_search(l, h, &ev);
		if (*sig != 0 || character(l, &ev) != 0 || key(l, h, &ev) != 0)
			break ;
		print_line(l, prompt);
	}
	if (*sig != 0)
		l->s[0] = '\0';
	print_line(l, prompt);
	ft_putendl("");
	return (linetos(l));
}
