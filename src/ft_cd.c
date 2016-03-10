/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 09:12:33 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 12:26:23 by nchrupal         ###   ########.fr       */
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
