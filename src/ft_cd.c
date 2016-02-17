/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 09:12:33 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/11 10:03:27 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include "libft.h"
#include "ft_cd.h"
#include "get_opts.h"
#include "parser.h"
#include "ft_env.h"
#include "error.h"
#include "ft_setenv.h"

char	*g_cd_opts = "LP";
t_flags	g_cd_valopts[] = { 0x1, 0x2 };

char	*get_nextid(char *s, char *name)
{
	int		i;

	if (*s == '/')
		s++;
	i = 0;
	while (*s && *s != '/')
	{
		name[i++] = *s;
		s++;
	}
	name[i] = '\0';
	return (s);
}

int		del_multipleslash(char *s, int len)
{
	char	*t;
	char	*sav;

	sav = s;
	while (*s)
	{
		if (*s == '/' && *(s + 1) == '/')
		{
			t = s + 1;
			while (*t == '/')
				t++;
			ft_strcpy(s + 1, t);
			len -= t - (s + 1);
		}
		s++;
	}
	sav[len] = '\0';
	return (len);
}

int		del_finalslash(char *s, int len)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	if (i > 1 && s[i - 1] == '/')
	{
		s[i - 1] = '\0';
		len--;
	}
	return (len);
}

int		del_dotslash(char *s, int len)
{
	char	name[BUFF_SZ + 1];
	char	*t;
	int		i;

	i = 0;
	while (i < len && s[i])
	{
		len = del_multipleslash(s, len);
		len = del_finalslash(s, len);
		t = get_nextid(s + i, name);
		if (ft_strcmp(name, ".") == 0)
		{
			ft_strcpy(s + i, t);
			len--;
			s[len] = '\0';
		}
		else
		{
			i += t - (s + i);
		}
	}
	s[len] = '\0';
	return (len);
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

int		del_dotdot(char *s, int len)
{
	char	name[BUFF_SZ + 1];
	char	*t;
	int		i;

	i = 0;
	while (i < len && s[i])
	{
		len = del_multipleslash(s, len);
		len = del_finalslash(s, len);
		t = get_nextid(s + i, name);
		if (ft_strcmp(name, "..") == 0)
		{
			s = move_dotdot(s, t, &len, i);
			i = 0;
		}
		else
			i += t - (s + i);
	}
	return (len);
}

int		convert_canonical(char *s)
{
	int		len;
	int		i;

	len = ft_strlen(s);
	i = 0;
	len = del_dotslash(s, len);
	len = del_dotdot(s, len);
	len = del_finalslash(s, len);
	len = del_finalslash(s, len);
	return (0);
}

t_flags	get_cdflags(t_tree *tree, int *i)
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
		if (ft_strcmp(s, "-") == 0)
			break ;
		if ((t = get_opts(s, g_cd_opts, g_cd_valopts, &flags)) == s)
			break ;
		if (*t != '\0')
		{
			g_errno = E_OPTION;
			eprintf("env: %s%c\n", g_error[g_errno], *t);
			eprintf("usage: cd [-L|-P] [directory]\n       cd -\n");
			break ;
		}
		*i = j;
	}
	flags = (flags == 0x0 || flags == 0x3) ? 0x1 : flags;
	return (flags);
}

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

int		changedir(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) < 0)
	{
		g_errno = E_NOFORDIR;
		return (eprintf("cd: %s: %s\n", path, g_error[g_errno]));
	}
	if ((buf.st_mode & S_IFMT) != S_IFDIR)
	{
		g_errno = E_ISNODIR;
		return (eprintf("cd: %s: %s\n", path, g_error[g_errno]));
	}
	if (chdir(path) < 0)
		return (eprintf("cd: could not open directory\n"));
	return (0);
}

t_env	*ft_cd(t_env *env, t_tree *tree)
{
	t_flags		flags;
	int			i;
	char		s[BUFF_SZ + 1];
	char		path[BUFF_SZ + 1];

	g_errno = E_NOERROR;
	flags = get_cdflags(tree, &i);
	if (g_errno)
		return (env);
	i = get_identifier(tree, i, s);
	if (set_cdstring(env, s) < 0)
		return (env);
	if (set_cdpath(env, path, s) < 0)
		return (env);
	convert_canonical(path);
	if (changedir(path) == 0)
		set_cdenv(env, path, s, flags);
	return (env);
}
