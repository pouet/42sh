/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_misc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:06:07 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 15:32:04 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_env.h"
#include "libft.h"
#include "parser.h"
#include "ft_setenv.h"
#include "xmalloc.h"

t_env	*env_newelement(char *s)
{
	const size_t	len = BUFF_SZ + 1;
	t_env			*tmp;

	tmp = ft_lstnew(xmalloc(len * sizeof(char)), len);
	if (tmp == NULL)
		return (NULL);
	ft_strncpy(tmp->content, s, BUFF_SZ);
	return (tmp);
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
	free(env->content);
	env->content = hash_createfile(env);
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
	tab = xmalloc((n + 1) * sizeof(*tab));
	tab[n] = NULL;
	i = 0;
	p = env->next;
	while (i < n)
	{
		tab[i] = xmalloc((BUFF_SZ + 1) * sizeof(**tab));
		ft_strncpy(tab[i], p->content, BUFF_SZ);
		p = p->next;
		i++;
	}
	return (tab);
}
