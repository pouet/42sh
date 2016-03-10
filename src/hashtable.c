/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 08:53:14 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 11:04:56 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include "ft_env.h"
#include "libft.h"
#include "hashtable.h"
#include "lexer.h"
#include "xmalloc.h"
#include "process_cmd.h"

t_hash		*hash_new(void)
{
	t_hash	*hash;

	hash = xmalloc((SZHASH + 1) * sizeof(*hash));
	ft_bzero(hash, (SZHASH + 1) * sizeof(*hash));
	return (hash);
}

void		hash_del(t_hash *hash)
{
	t_hash	*tmp;
	int		i;

	if (hash == NULL)
		return ;
	i = 0;
	while (i < SZHASH)
	{
		while (hash[i].next != NULL)
		{
			tmp = hash[i].next->next;
			free(hash[i].next);
			hash[i].next = tmp;
		}
		i++;
	}
	free(hash);
}

unsigned	hash_key(char *cmd)
{
	unsigned	key;

	key = 0;
	while (*cmd)
	{
		key = key * SZHASH + *cmd;
		cmd++;
	}
	return (key % SZHASH);
}

t_hash		*hash_exist(t_hash *hash, char *cmd)
{
	unsigned	key;
	t_hash		*tmp;

	key = hash_key(cmd);
	tmp = hash + key;
	while (tmp != NULL && ft_strcmp(tmp->cmd, cmd) != 0)
		tmp = tmp->next;
	return (tmp);
}

t_hash		*hash_nameupdate(t_hash *hash, char *cmd)
{
	t_hash	*new;
	t_hash	*tmp;

	tmp = hash + SZHASH;
	while (tmp->next != NULL && ft_strcmp(tmp->next->cmd, cmd) < 0)
		tmp = tmp->next;
	if (tmp->next != NULL && ft_strcmp(tmp->next->cmd, cmd) == 0)
		return (hash);
	new = xmalloc(sizeof(*new));
	ft_bzero(new, sizeof(*new));
	ft_strcpy(new->cmd, cmd);
	if (tmp->next == NULL)
		tmp->next = new;
	else
	{
		new->next = tmp->next;
		tmp->next = new;
	}
	return (hash);
}

t_hash		*hash_insert(t_hash *hash, char *cmd, char *fullpath)
{
	unsigned	key;
	t_hash		*tmp;
	t_hash		*new;

	key = hash_key(cmd);
	tmp = hash + key;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->cmd[0] != '\0')
	{
		new = xmalloc(sizeof(*new));
		ft_bzero(new, sizeof(*new));
		tmp->next = new;
		tmp = new;
	}
	tmp->key = key;
	ft_strlcat(tmp->cmd, cmd, BUFF_SZ);
	ft_strlcat(tmp->fullpath, fullpath, BUFF_SZ);
	hash_nameupdate(hash, cmd);
	return (hash);
}

void		hash_addfile(t_hash *hash, char *path)
{
	struct dirent	*dp;
	DIR				*dirp;
	char			file[BUFF_SZ + 1];

	dirp = opendir(path);
	if (dirp == NULL)
		return ;
	while ((dp = readdir(dirp)) != NULL)
	{
		ft_strncpy(file, path, BUFF_SZ);
		ft_strlcat(file, dp->d_name, BUFF_SZ);
		if (ft_strcmp(dp->d_name, ".") != 0 &&
				ft_strcmp(dp->d_name, "..") != 0 &&
				access(file, X_OK) == 0)
			hash_insert(hash, dp->d_name, file);
	}
	closedir(dirp);
}

t_hash		*hash_createfile(t_env *env)
{
	char	full[BUFF_SZ + 1];
	char	*path;
	char	*p;
	t_env	*env_path;
	t_hash	*hash;

	hash = hash_new();
	env_path = env_getname(env, "PATH");
	if (env_path == NULL)
		return (hash);
	path = env_path->content + 5;
	while (*path)
	{
		p = create_path(full, path, "");
		hash_addfile(hash, full);
		if (p == NULL)
			break ;
		path = p + 1;
	}
	return (hash);
}

t_hash		*hash_update(t_env *env)
{
	hash_del(env->content);
	env->content = hash_createfile(env);
	return (env->content);
}
