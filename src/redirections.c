/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 11:06:05 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 14:10:28 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/syslimits.h>
#include <limits.h>
#include "libft.h"
#include "redirections.h"
#include "lexer.h"
#include "parser.h"
#include "error.h"
#include "read_line.h"
#include "initterms.h"

int		get_nbr(char *s, char **t)
{
	int				sign;
	unsigned long	n;

	n = 0;
	sign = 1;
	if (*s == '-')
		sign = -1 * (*s++ == '-');
	while (n < (unsigned long)INT_MAX + 1 && ft_isdigit(*s))
		n = n * 10 + *s++ - '0';
	if (n > (unsigned long)INT_MAX ||
		(n > (unsigned long)INT_MAX + 1 && sign < 0))
	{
		n = INT_MAX;
		s--;
	}
	*t = s;
	return (n * sign);
}

void	del_redir(t_tree *tree, int start, int end)
{
	int		i;

	i = start;
	while (i < end)
	{
		tree->child[i]->type = T_NAME;
		tree->child[i]->token->sym = S_SEPARATOR;
		i++;
	}
}

int		do_redirection(t_tree *tree, int i)
{
	char	s[BUFF_SZ + 1];
	int		j;
	int		ret;

	ret = 0;
	j = get_identifier(tree, i + 1, s);
	if (i + 1 >= tree->nchild || s[0] == '\0')
	{
		g_errno = E_SYNTAX;
		return (eprintf("%s '%s'\n",
					g_error[g_errno], tree->child[i]->token->s));
	}
	if (tree->child[i]->token->sym == S_REDIRIN ||
			tree->child[i]->token->sym == S_REDIROUT ||
			tree->child[i]->token->sym == S_APPENDOUT)
		ret = redir(tree->child[i]->token->sym, tree->child[i]->token->s, s);
	else if (tree->child[i]->token->sym == S_DUPIN ||
			tree->child[i]->token->sym == S_DUPOUT)
		ret = dup_fd(tree->child[i]->token->sym, tree->child[i]->token->s, s);
	else if (tree->child[i]->token->sym == S_HEREDOC)
		ret = heredoc(tree->child[i]->token->sym, tree->child[i]->token->s, s);
	del_redir(tree, i, j);
	return (ret);
}

int		cmd_redirection(t_tree *tree)
{
	int		i;

	i = 1;
	while (!g_errno && i < tree->nchild)
	{
		if (tree->child[i]->type == T_REDIR)
			if (do_redirection(tree, i) < 0)
				g_errno = E_BADFD;
		i++;
	}
	return (0);
}

int		oper_redirection(t_tree *tree)
{
	int		i;

	if (g_errno)
		return (-1);
	if (tree)
	{
		if (tree->type == T_CMD)
			cmd_redirection(tree);
		else
		{
			i = 0;
			while (i < tree->nchild)
			{
				oper_redirection(tree->child[i]);
				i++;
			}
		}
	}
	return (0);
}
