/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:35:27 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 14:39:53 by nchrupal         ###   ########.fr       */
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

int		path_count(t_line *l, char *path, char *file, char *res)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				n;
	int				len;

	(void)l;
	dirp = opendir(path);
	if (dirp == NULL)
		return (0);
	n = 0;
	len = ft_strlen(file);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (ft_strncmp(dp->d_name, file, len) == 0)
		{
			ft_strcpy(res, dp->d_name);
			n++;
		}
	}
	closedir(dirp);
	return (n);
}

int		path_complete(t_line *l, char *s, int len)
{
	while (s[len])
	{
		add_char(l, s[len]);
		len++;
	}
	return (0);
}

int		path_multiple(t_line *l, char *path, char *file)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				n;
	int				len;

	(void)l;
	dirp = opendir(path);
	if (dirp == NULL)
		return (0);
	ft_putendl("");
	n = 0;
	len = ft_strlen(file);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (ft_strncmp(dp->d_name, file, len) == 0)
		{
			ft_putendl(dp->d_name);
		}
	}
	closedir(dirp);
	return (1);
}

void	path_expand(t_token *token, t_env *env, char *s, int len)
{
	t_tree	tree;

	tree.type = T_NAME;
	tree.token = token;
	tree.token->sym = S_IDENT;
	ft_strncpy(token->s, s, len);
	token->s[len] = '\0';
	expand_tilde(&tree, env);
	if (token->s[0] != '/')
	{
		getcwd(token->s, BUFF_SZ);
		ft_strlcat(token->s, "/", BUFF_SZ);
		ft_strlcat(token->s, s, BUFF_SZ);
	}
}

int		path_completion(t_line *l, t_env *env, char *s, int len)
{
	t_token	token;
	char	*t;
	char	res[BUFF_SZ + 1];
	int		npath;

	path_expand(&token, env, s, len);
	t = token.s + ft_strlen(token.s);
	while (t > token.s && *t != '/')
		t--;
	if (t == token.s && *t == '/')
	{
		ft_memmove(token.s + 1, token.s, ft_strlen(token.s) + 1);
		token.s[1] = '\0';
		t = token.s + 2;
	}
	else if (t != token.s && *t == '/')
		*t++ = '\0';
	npath = path_count(l, token.s, t, res);
	if (npath == 1)
		return (path_complete(l, res, ft_strlen(t)));
	else if (npath > 1)
		return (path_multiple(l, token.s, t));
	return (0);
}
