/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 08:29:18 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 14:38:47 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include "expand.h"
#include "parser.h"
#include "lexer.h"
#include "ft_printf.h"
#include "libft.h"
#include "completion.h"
#include "print.h"
#include "ft_env.h"
#include "read_line.h"
#include "hashtable.h"
#include "move.h"
#include "cmd_completion.h"
#include "path_completion.h"

int		is_firstword(t_line *l, char *s)
{
	int		first;

	first = 0;
	s--;
	while (s > l->s && (*s == ' '))
	{
		s--;
	}
	if (s <= l->s || *s == ';' || *s == '|' || *s == '&')
		return (1);
	return (0);
}

int		add_completion(t_line *l, char *s, int len)
{
	while (s[len])
	{
		add_char(l, s[len]);
		len++;
	}
	return (1);
}

int		completion(t_line *l, t_env *env)
{
	char	*s;
	int		len;

	s = l->s + l->i - 1;
	while (s > l->s && (*s != ' ' && *s != ';' && *s != '|' && *s != '&' &&
		*s != '>' && *s != '<' && *s != '(' && *s != ')'))
		s--;
	if (s != l->s)
		s++;
	len = (l->s + l->i) - s;
	if (is_firstword(l, s) && ft_strncmp(s, "./", 2) != 0
			&& ft_strncmp(s, "../", 3) != 0)
		return (cmd_completion(l, env, s, len));
	else
		return (path_completion(l, env, s, len));
}
