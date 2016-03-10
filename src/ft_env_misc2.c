/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_misc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:08:22 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 12:13:17 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_env.h"
#include "ft_setenv.h"
#include "parser.h"

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

void	print_env(t_env *env)
{
	env = env->next;
	while (env)
	{
		ft_putendl(env->content);
		env = env->next;
	}
}
