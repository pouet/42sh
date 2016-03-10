/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 08:53:14 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 12:18:49 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include "ft_env.h"
#include "libft.h"
#include "ft_env.h"
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
