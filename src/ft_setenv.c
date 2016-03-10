/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 11:12:22 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 08:48:48 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_setenv.h"
#include "lexer.h"
#include "ft_env.h"
#include "parser.h"
#include "error.h"
#include "hashtable.h"

/*
** name_value => NAME=VALUE
** si la forme n'est pas respectee, l'env n'est pas modifie
*/

t_env	*ft_setenv_byname(t_env *env, char *name_value)
{
	char	name[BUFF_SZ + 1];
	char	*value;
	size_t	len;
	t_env	*tmp;

	value = ft_strchr(name_value, '=');
	if (value == NULL || !ft_isalpha(*name_value))
	{
		eprintf("setenv: must be the form : NAME=VALUE\n");
		return (env);
	}
	len = value - name_value;
	ft_strncpy(name, name_value, len);
	name[len] = '\0';
	value++;
	tmp = env_getname(env, name);
	if (tmp == NULL)
		env = ft_lstpushback(env, env_newelement(name_value));
	else
		ft_strncpy(tmp->content, name_value, BUFF_SZ);
	if (ft_strncmp(name_value, "PATH=", 5) == 0)
		hash_update(env);
	return (env);
}

t_env	*ft_setenv(t_env *env, t_tree *tree)
{
	char	tmp[BUFF_SZ + 1];
	int		i;

	i = 1;
	while (i < tree->nchild)
	{
		i = get_identifier(tree, i, tmp);
		if (ft_strchr(tmp, '=') == NULL)
		{
			eprintf("setenv: must be the form : NAME=VALUE\n");
			break ;
		}
		env = ft_setenv_byname(env, tmp);
		i++;
	}
	return (env);
}

t_env	*ft_unsetenv_byname(t_env *env, char *name)
{
	char	*value;
	t_env	*tmp;
	t_env	*p;

	if ((value = ft_strchr(name, '=')) != NULL)
	{
		eprintf("unsetenv: wrong identifier\n");
		return (env);
	}
	if ((tmp = env_getname(env, name)) == NULL)
	{
		eprintf("unsetenv: unknown name %s\n", name);
		return (env);
	}
	if (tmp == env)
		env = tmp->next;
	p = env;
	while (p->next != tmp)
		p = p->next;
	p->next = tmp->next;
	free(tmp->content);
	free(tmp);
	if (ft_strcmp(name, "PATH") == 0)
		hash_update(env);
	return (env);
}

t_env	*ft_unsetenv(t_env *env, t_tree *tree)
{
	char	tmp[BUFF_SZ + 1];
	int		i;

	i = 1;
	while (i < tree->nchild)
	{
		i = get_identifier(tree, i, tmp);
		env = ft_unsetenv_byname(env, tmp);
		i++;
	}
	return (env);
}
