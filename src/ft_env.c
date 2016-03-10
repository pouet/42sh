/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 11:43:42 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 12:08:48 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_env.h"
#include "lexer.h"
#include "parser.h"
#include "get_opts.h"
#include "ft_setenv.h"
#include "process_cmd.h"
#include "error.h"

char	*g_env_opts = "i";
t_flags	g_env_valopts[] = { 0x1 };

t_tree	*env_tree(t_tree *tree, int begin)
{
	int		i;
	int		j;

	i = 0;
	while (i < begin)
		deltree(tree->child[i++]);
	i = 0;
	j = begin;
	while (j < tree->nchild)
	{
		tree->child[i] = tree->child[j];
		i++;
		j++;
	}
	tree->nchild = i;
	return (tree);
}

t_flags	get_envflags(t_tree *tree, int *i)
{
	t_flags	flags;
	char	s[BUFF_SZ + 1];
	int		j;
	char	*t;

	flags = 0;
	*i = 1;
	while (*i < tree->nchild)
	{
		j = get_identifier(tree, *i, s);
		if (*s != '-')
			break ;
		t = get_opts(s, g_env_opts, g_env_valopts, &flags);
		if (t == s)
			break ;
		if (*t != '\0')
		{
			g_errno = E_OPTION;
			eprintf("env: %s%c\n", g_error[g_errno], *t);
			eprintf("usage: env [-i] [name=val]... [utility [argument...]]\n");
			break ;
		}
		*i = j;
	}
	return (flags);
}

t_env	*apply_varenv(t_env *env, t_tree *tree, int *i)
{
	char	tmp[BUFF_SZ + 1];
	int		j;

	while (*i < tree->nchild)
	{
		j = get_identifier(tree, *i, tmp);
		if (tmp[0] == '\0' || !ft_strchr(tmp, '='))
			break ;
		env = ft_setenv_byname(env, tmp);
		*i = j + 1;
	}
	return (env);
}

t_env	*ft_env(t_env *env, t_tree *tree)
{
	t_env		*dup;
	t_flags		flags;
	int			i;

	g_errno = E_NOERROR;
	flags = get_envflags(tree, &i);
	if (g_errno)
		return (env);
	dup = dup_env(env);
	if (flags & g_env_valopts[0])
		dup = free_env(dup);
	dup = apply_varenv(dup, tree, &i);
	while (i < tree->nchild && tree->child[i]->token->sym == S_SEPARATOR)
		i++;
	if (i >= tree->nchild)
		print_env(dup);
	else
	{
		env_tree(tree, i);
		process_cmd(tree, env, dup);
	}
	free_env(dup);
	free(dup);
	return (env);
}
