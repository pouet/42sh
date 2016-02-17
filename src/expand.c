/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 15:15:52 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/11 10:10:25 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "expand.h"
#include "lexer.h"
#include "parser.h"
#include "error.h"

void	expand_brace(t_tree *tree, t_env *env)
{
	(void)tree;
	(void)env;
}

/*
** if HOME is unset: getpwuid() => pwd_dir
*/

void	expand_tilde(t_tree *tree, t_env *env)
{
	t_env	*path;
	char	*name;
	char	buf[BUFF_SZ + 1];
	int		off;

	if (tree->type == T_NAME && (tree->token->sym == S_IDENT)
			&& tree->token->s[0] == '~')
	{
		name = "HOME";
		if (tree->token->s[1] == '+')
			name = "PWD";
		else if (tree->token->s[1] == '-')
			name = "OLDPWD";
		path = env_getname(env, name);
		if (path == NULL)
			eprintf("expand tilde: %s not set\n", name);
		else
		{
			off = ft_strlen(name) + 1;
			ft_strncpy(buf, (char *)path->content + off, BUFF_SZ);
			off = 1 + !!ft_strcmp(name, "HOME");
			ft_strlcat(buf, tree->token->s + off, BUFF_SZ);
			ft_strncpy(tree->token->s, buf, BUFF_SZ);
		}
	}
}

void	variable_substitution(t_tree *tree, t_env *env)
{
	(void)tree;
	(void)env;
}

void	command_substitution(t_tree *tree, t_env *env)
{
	(void)tree;
	(void)env;
}

void	quote_removal(t_tree *tree, t_env *env)
{
	(void)env;
	if (tree->type == T_NAME &&
		(tree->token->sym == S_DQUOTE || tree->token->sym == S_SQUOTE))
	{
		tree->token->slen -= 2;
		ft_memmove(tree->token->s, tree->token->s + 1, tree->token->slen);
		tree->token->s[tree->token->slen] = '\0';
		tree->token->sym = S_IDENT;
	}
}

void	expand_all(t_tree *tree, t_env *env)
{
	int		i;

	if (tree)
	{
		i = 0;
		while (i < tree->nchild)
		{
			expand_all(tree->child[i], env);
			i++;
		}
		expand_brace(tree, env);
		expand_tilde(tree, env);
		variable_substitution(tree, env);
		command_substitution(tree, env);
		quote_removal(tree, env);
	}
}
