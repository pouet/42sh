/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 13:49:56 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 13:59:12 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lexer.h"
#include "error.h"

int		is_token(char *s)
{
	size_t		i;

	i = 0;
	while (g_symbol[i].len > 0)
	{
		if (ft_strncmp(s, g_symbol[i].s, g_symbol[i].len) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*get_quoted_string(t_token *token, char *s)
{
	int		len;
	char	*t;

	t = ft_strchr(s, g_symbol[token->sym].s[0]);
	if (t == NULL)
	{
		eprintf("error: missing quote\n");
		token->sym = S_UNKNOWN;
		return (s + 1);
	}
	len = t - s + 1;
	token->s[0] = g_symbol[token->sym].s[0];
	ft_strncpy(token->s + 1, s, len);
	token->s[len + 1] = '\0';
	token->slen = len + 1;
	return (t + 1);
}

char	*get_redir(t_token *token, char *s)
{
	const int	tab[] = { S_HEREDOC, S_APPENDOUT, S_DUPIN, S_DUPOUT, S_REDIRIN,
		S_REDIROUT };
	char		*t;
	int			i;

	t = s;
	token->sym = S_UNKNOWN;
	while (*s && ft_isdigit(*s))
		s++;
	i = 0;
	while (token->sym == S_UNKNOWN && i < (int)(sizeof(tab) / sizeof(*tab)))
	{
		if (!ft_strncmp(s, g_symbol[tab[i]].s, g_symbol[tab[i]].len))
			token->sym = tab[i];
		i++;
	}
	if (token->sym == S_UNKNOWN)
		return (t);
	s += g_symbol[token->sym].len;
	token->slen = s - t;
	ft_strncpy(token->s, t, token->slen);
	token->s[token->slen] = '\0';
	return (s);
}

char	*get_name(t_token *token, char *s)
{
	int		i;

	s = get_redir(token, s);
	if (token->sym != S_UNKNOWN)
		return (s);
	token->sym = S_IDENT;
	i = 0;
	while (*s && !ft_isspace(*s) && !is_token(s))
	{
		token->s[i] = *s;
		s++;
		i++;
	}
	token->s[i] = '\0';
	token->slen = i;
	return (s);
}
