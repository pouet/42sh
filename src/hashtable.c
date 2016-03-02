/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 08:53:14 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/02 10:14:50 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "parser.h"
#include "xmalloc.h"

# define SZHASH 97

typedef struct	s_hash
{
	unsigned		key;
	char			cmd[BUFF_SZ + 1];
	char			fullpath[BUFF_SZ + 1];
	struct s_hash	*next;
}				t_hash;

t_hash	*hash_new(void)
{
	t_hash	*hash;

	hash = xmalloc(SZHASH * sizeof(*hash));
	ft_bzero(hash, SZHASH * sizeof(*hash));
	return (hash);
}

void	hash_del(t_hash *hash)
{
	t_hash	*tmp;
	int		i;

	if (hash == NULL)
		return ;
	i = 0;
	while (i < SZHASH)
	{
		while (hash[i] != NULL)
		{
			tmp = hash[i]->next;
			free(hash[i]);
			hash[i] = tmp;
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

t_hash	*hash_exist(t_hash *hash, char *cmd)
{
	unsigned	key;
	t_hash		*tmp;

	key = hash_key(cmd);
	tmp = hash[key];
	while (tmp != NULL && tmp->key != key && ft_strcmp(tmp->cmd, cmd) != 0)
		tmp = tmp->next;
	return (tmp);
}

t_hash	*hash_insert(t_hash *hash, char *cmd, char *fullpath)
{
	unsigned	key;
	t_hash		*tmp;
	t_hash		*new;

	key = hash_key(cmd);
	tmp = hash[key];
	while (tmp->key != key && tmp->cmd[0] != '\0' && tmp->next != NULL)
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
	return (hash);
}
