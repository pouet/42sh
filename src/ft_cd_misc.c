/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:22:58 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 12:29:16 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_cd.h"
#include "get_opts.h"
#include "ft_env.h"
#include "ft_setenv.h"
#include "error.h"

extern t_flags	g_cd_valopts[];

int		set_cdstring(t_env *env, char *s)
{
	t_env		*home;
	t_env		*oldpwd;

	home = env_getname(env, "HOME");
	oldpwd = env_getname(env, "OLDPWD");
	if (s[0] == '\0' && home == NULL)
		return (eprintf("cd: HOME not set\n"));
	else if (s[0] == '\0')
		ft_strncpy(s, (char *)home->content + 5, BUFF_SZ);
	else if (s[0] == '/' || (s[0] == '.' && s[1] == '.'))
		ft_strncpy(s, s, BUFF_SZ);
	else if (ft_strcmp(s, "-") == 0)
	{
		if (oldpwd == NULL)
			return (eprintf("cd: OLDPWD not set\n"));
		ft_strncpy(s, (char *)oldpwd->content + 7, BUFF_SZ);
	}
	return (0);
}

int		set_cdpath(t_env *env, char *path, char *s)
{
	t_env	*pwd;
	int		len;

	pwd = env_getname(env, "PWD");
	if (pwd == NULL)
	{
		ft_setenv_byname(env, "PWD=");
		pwd = env_getname(env, "PWD");
	}
	path[0] = '\0';
	if (s[0] != '/')
	{
		ft_strncpy(path, (char *)pwd->content + 4, BUFF_SZ);
		len = ft_strlen(path);
		if (len > 0 && path[len - 1] != '/')
			ft_strlcat(path, "/", BUFF_SZ);
	}
	ft_strlcat(path, s, BUFF_SZ);
	return (0);
}

int		set_cdenv(t_env *env, char *path, char *s, t_flags flags)
{
	t_env	*pwd;

	pwd = env_getname(env, "PWD");
	ft_strncpy(s, "OLDPWD=", BUFF_SZ);
	ft_strlcat(s, ((char *)pwd->content) + 4, BUFF_SZ);
	ft_setenv_byname(env, s);
	ft_strncpy(s, "PWD=", BUFF_SZ);
	if (flags & g_cd_valopts[1])
		getcwd(path, BUFF_SZ);
	ft_strlcat(s, path, BUFF_SZ);
	ft_setenv_byname(env, s);
	return (0);
}

char	*move_dotdot(char *s, char *t, int *len, int i)
{
	while (i > 0 && s[i - 1] != '/')
		i--;
	if (i == 0)
	{
		eprintf("cd: root have no parent...: '/' used instead\n");
		ft_strcpy(s + 1, s + 3);
		*len -= 2;
	}
	else
	{
		ft_strcpy(s + i, t);
		*len = *len - (t - (s + i));
	}
	s[*len] = '\0';
	return (s);
}
