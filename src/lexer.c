/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 10:25:49 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 15:32:30 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lexer.h"
#include "error.h"
#include "xmalloc.h"

#define X(e, s, len) { s, len },

/*
** MUST BE IN LENGTH REVERSE ORDER
*/
t_string	g_symbol[S_MAX + 1] = {
	MACRO
};

#undef X

char	*get_symbol(t_token *token, char *s)
{
	size_t		i;

	i = 0;
	token->sym = S_UNKNOWN;
	while (g_symbol[i].len > 0)
	{
		if (ft_strncmp(s, g_symbol[i].s, g_symbol[i].len) == 0)
		{
			token->sym = i;
			ft_strncpy(token->s, g_symbol[i].s, g_symbol[i].len);
			token->slen = g_symbol[i].len;
			token->s[token->slen] = '\0';
			s += g_symbol[i].len;
			break ;
		}
		i++;
	}
	return (s);
}

char	*get_separator(t_token *token, char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	token->sym = S_SEPARATOR;
	token->s[0] = '\0';
	token->slen = 0;
	return (s);
}

t_token	get_next_token(char *s, char **t)
{
	t_token		token;

	if (ft_isspace(*s))
	{
		*t = get_separator(&token, s);
		return (token);
	}
	if (*s == '\0')
	{
		token.sym = S_EOL;
		*t = s;
		return (token);
	}
	s = get_symbol(&token, s);
	if (token.sym == S_DQUOTE || token.sym == S_SQUOTE
			|| token.sym == S_BACKQUOTE)
		s = get_quoted_string(&token, s);
	else if (token.sym == S_UNKNOWN)
		s = get_name(&token, s);
	*t = s;
	return (token);
}

t_token	*lexer(char *s)
{
	t_token	token[BUFF_SZ + 1];
	t_token	*tmp;
	int		i;

	i = 0;
	while (i < BUFF_SZ)
	{
		token[i] = get_next_token(s, &s);
		if (token[i].sym == S_UNKNOWN)
		{
			return (NULL);
		}
		if (token[i].sym == S_EOL)
			break ;
		i++;
	}
	tmp = xmalloc((i + 1) * sizeof(*tmp));
	ft_memcpy(tmp, token, (i + 1) * sizeof(*tmp));
	return (tmp);
}
