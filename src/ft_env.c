/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 11:43:42 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/11 09:19:03 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_env.h"
#include "lexer.h"
#include "parser.h"
#include "get_opts.h"
#include "ft_setenv.h"
#include "process_cmd.h"
#include "error.h"

char	*g_env_opts = "i";
t_flags	g_env_valopts[] = { 0x1 };

t_env	*env_newelement(char *s)
{
	const size_t	len = BUFF_SZ + 1;
	t_env			*tmp;

	tmp = ft_lstnew(malloc(len * sizeof(char)), len);
	if (tmp == NULL)
		return (NULL);
	ft_strncpy(tmp->content, s, BUFF_SZ);
	return (tmp);
}

t_env	*set_shlvl(t_env *env)
{
	t_env	*tmp;
	int		n;
	char	s[BUFF_SZ + 1];
	char	*t;

	n = 1;
	tmp = env_getname(env, "SHLVL");
	if (tmp != NULL)
	{
		n = 0;
		n = ft_atoi((char *)tmp->content + 6);
		if (n <= 0)
			n = 1;
		else
			n++;
	}
	t = ft_itoa(n);
	ft_strcpy(s, "SHLVL=");
	ft_strcat(s, t);
	free(t);
	return (ft_setenv_byname(env, s));
}

t_env	*create_env_environ(void)
{
	extern char		**environ;
	int				n;
	t_env			*env;
	char			s[BUFF_SZ + 1];

	env = NULL;
	env = ft_lstpushback(env, env_newelement(""));
	n = 0;
	while (environ[n] != NULL)
	{
		env = ft_lstpushback(env, env_newelement(environ[n]));
		n++;
	}
	if (env_getname(env, "PWD") == NULL)
	{
		ft_strcpy(s, "PWD=");
		getcwd(s + 4, BUFF_SZ - 4);
		env = ft_setenv_byname(env, s);
	}
	env = set_shlvl(env);
	return (env);
}

t_env	*dup_env(t_env *env)
{
	t_env			*dup;

	dup = NULL;
	while (env)
	{
		dup = ft_lstpushback(dup, env_newelement(env->content));
		env = env->next;
	}
	return (dup);
}

t_env	*env_getname(t_env *env, char *name)
{
	int		len;
	char	*s;

	len = ft_strlen(name);
	while (env)
	{
		s = env->content;
		if (ft_strncmp(s, name, len) == 0 && s[len] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*free_env(t_env *env)
{
	t_env		*p;
	t_env		*tmp;

	p = env->next;
	env->next = NULL;
	while (p)
	{
		tmp = p->next;
		free(p->content);
		free(p);
		p = tmp;
	}
	return (env);
}

void	print_env(t_env *env)
{
	env = env->next;
	while (env)
	{
		ft_putstr("-> ");
		ft_putendl(env->content);
		env = env->next;
	}
}

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
		if (j >= tree->nchild || *s != '-')
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

char	**env_totab(t_env *env)
{
	int		n;
	int		i;
	t_env	*p;
	char	**tab;

	n = 0;
	p = env->next;
	while (p)
	{
		p = p->next;
		n++;
	}
	tab = malloc((n + 1) * sizeof(*tab));
	tab[n] = NULL;
	i = 0;
	p = env->next;
	while (i < n)
	{
		tab[i] = malloc((BUFF_SZ + 1) * sizeof(**tab));
		ft_strncpy(tab[i], p->content, BUFF_SZ);
		p = p->next;
		i++;
	}
	return (tab);
}
