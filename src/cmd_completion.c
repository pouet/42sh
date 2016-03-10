/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:32:00 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 15:21:48 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include "expand.h"
#include "parser.h"
#include "lexer.h"
#include "ft_printf.h"
#include "libft.h"
#include "completion.h"
#include "print.h"
#include "ft_env.h"
#include "read_line.h"
#include "hashtable.h"
#include "move.h"
#include "cmd_completion.h"

int		cmd_count(t_hash *hash, char *s, int len)
{
	int		n;

	n = 0;
	while (hash && ft_strncmp(hash->cmd, s, len) == 0)
	{
		n++;
		hash = hash->next;
	}
	return (n);
}

int		cmd_lenmax(t_hash *hash, int ncmd)
{
	int		lenmax;
	int		len;
	int		i;

	lenmax = 0;
	i = 0;
	while (hash && i < ncmd)
	{
		len = ft_strlen(hash->cmd);
		if (len > lenmax)
			lenmax = len;
		hash = hash->next;
		i++;
	}
	return (lenmax);
}

void	print_cmd(t_line *l, t_hash *hash, int ncmd, int lenmax)
{
	int		len;
	int		col;
	int		wid;
	int		i;
	int		j;

	col = l->wincol / (lenmax + 1);
	wid = l->wincol / col;
	j = 0;
	while (j < ncmd)
	{
		if (j != 0 && j % col == 0)
			ft_putchar('\n');
		len = ft_strlen(hash->cmd);
		ft_putstr(hash->cmd);
		i = len;
		while (i < wid)
		{
			ft_putchar(' ');
			i++;
		}
		hash = hash->next;
		j++;
	}
	ft_putchar('\n');
}

int		cmd_multiple(t_line *l, t_hash *hash, int ncmd)
{
	char	c;

	movecur_last(l);
	if (ncmd > 100)
	{
		ft_printf("Display all %d possibilities ? (y/n)", ncmd);
		while (read(0, &c, 1) > 0 && c != 'y' && c != 'n')
			;
		ft_putendl("");
		if (c == 'n')
			return (0);
	}
	print_cmd(l, hash, ncmd, cmd_lenmax(hash, ncmd));
	return (1);
}

int		cmd_completion(t_line *l, t_env *env, char *s, int len)
{
	t_hash	*hash;
	int		ncmd;

	if (env == NULL)
		return (0);
	hash = env->content;
	hash = hash + SZHASH;
	hash = hash->next;
	while (hash != NULL)
	{
		ncmd = cmd_count(hash, s, len);
		if (ncmd == 1)
		{
			add_completion(l, hash->cmd, len);
			break ;
		}
		if (ncmd > 0)
		{
			cmd_multiple(l, hash, ncmd);
			return (1);
		}
		hash = hash->next;
	}
	return (0);
}
