/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:25:37 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 15:04:06 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include "libft.h"
#include "ft_printf.h"
#include "process_cmd.h"
#include "initterms.h"
#include "lexer.h"
#include "parser.h"
#include "ft_env.h"
#include "ft_setenv.h"
#include "error.h"
#include "ft_cd.h"
#include "ft_exit.h"
#include "redirections.h"
#include "hashtable.h"
#include "save_restore.h"
#include "pipe_cmd.h"

extern t_builtinlist g_bt[NBUILTIN];

int		is_builtin(char *s)
{
	int		i;

	i = 0;
	while (i < NBUILTIN)
	{
		if (ft_strcmp(g_bt[i].name, s) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*create_path(char *file, char *path, char *s)
{
	int		len;
	char	*p;

	len = BUFF_SZ;
	p = ft_strchr(path, ':');
	if (p != NULL)
		len = p - path;
	ft_strncpy(file, path, len);
	file[len] = '\0';
	if (len == 0)
		ft_strcpy(file, ".");
	ft_strlcat(file, "/", BUFF_SZ);
	ft_strlcat(file, s, BUFF_SZ);
	return (p);
}

int		have_permission(char *cmd)
{
	struct stat	buf;
	uid_t		uid;
	gid_t		gid;

	uid = getuid();
	gid = getgid();
	if (stat(cmd, &buf) < 0)
		return (-1);
	if (((buf.st_uid == uid && (buf.st_mode & S_IXUSR)) ||
			(buf.st_gid == gid && (buf.st_mode & S_IXGRP)) ||
			(buf.st_mode & S_IXOTH)) &&
		((buf.st_mode & S_IFMT) == S_IFREG))
		return (1);
	g_errno = E_PERMISSION;
	eprintf("%s: %s\n", cmd, g_error[g_errno]);
	return (0);
}

int		is_pathsearch(char *s, t_env *env)
{
	t_hash	*hash;

	hash = hash_exist(env->content, s);
	if (hash == NULL || access(hash->fullpath, X_OK) != 0)
	{
		hash_update(env);
		hash = hash_exist(env->content, s);
	}
	if (hash != NULL && have_permission(hash->fullpath) &&
			access(hash->fullpath, X_OK) == 0)
	{
		ft_strncpy(s, hash->fullpath, BUFF_SZ);
		return (1);
	}
	return (0);
}

int		find_cmd(t_token *token, t_env *env)
{
	int		ret;

	if (token == NULL || ft_strcmp(token->s, ".") == 0
		|| ft_strcmp(token->s, "..") == 0)
		return (0);
	if (ft_strchr(token->s, '/'))
	{
		if (have_permission(token->s) == 0 || access(token->s, X_OK) != 0)
			return (0);
		token->sym = S_COMMAND;
	}
	else
	{
		if ((ret = is_builtin(token->s)) >= 0)
		{
			token->sym = S_BUILTIN;
			token->btin_num = ret;
		}
		else if (is_pathsearch(token->s, env))
			token->sym = S_COMMAND;
		else
			return (0);
	}
	return (1);
}
