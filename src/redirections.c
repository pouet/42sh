/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 11:06:05 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/16 14:36:25 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "redirections.h"
#include "lexer.h"
#include "parser.h"
#include "error.h"

int		redir_in(t_tree *tree, char *redir, char *word)
{
	int		fd;
	int		fd_src;

	fd_src = 0;
	if (ft_isdigit(*redir))
	{
		while (ft_isdigit(*redir) && fd_src <= MAX_FD)
			fd_src = fd_src * 10 + *redir++ - '0';
		if (fd_src >= MAX_FD)
			return (eprintf("error: bad file descriptor\n"));
	}
	fd = open(word, O_RDONLY);
	if (fd < 0)
		/* TODO: gerer mieux les erreurs */
		return (eprintf("error: bad file descriptor\n"));
	dup2(fd, fd_src);
	return (0);
}

int		redir_out(t_tree *tree, char *redir, char *word)
{
	int		fd;
	int		fd_src;

	fd_src = 1;
	if (ft_isdigit(*redir))
	{
		fd_src = 0;
		while (ft_isdigit(*redir) && fd_src <= MAX_FD)
			fd_src = fd_src * 10 + *redir++ - '0';
		if (fd_src >= MAX_FD)
			return (eprintf("error: bad file descriptor\n"));
	}
	fd = open(word, O_WRONLY | O_CREAT | O_TRUNC,
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		/* TODO: gerer mieux les erreurs */
		return (eprintf("error: bad file descriptor\n"));
	dup2(fd, fd_src);
	return (0);
}

int		append_out(t_tree *tree, char *redir, char *word)
{
	int		fd;
	int		fd_src;

	fd_src = 1;
	if (ft_isdigit(*redir))
	{
		fd_src = 0;
		while (ft_isdigit(*redir) && fd_src <= MAX_FD)
			fd_src = fd_src * 10 + *redir++ - '0';
		if (fd_src >= MAX_FD)
			return (eprintf("error: bad file descriptor\n"));
	}
	fd = open(word, O_WRONLY | O_CREAT | O_APPEND,
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		/* TODO: gerer mieux les erreurs */
		return (eprintf("error: appendout: bad file descriptor\n"));
	dup2(fd, fd_src);
	return (0);
}

int		dup_in(t_tree *tree, char *redir, char *word)
{
	int		fd_src;
	int		fd_dst;

	fd_dst = 0;
	if (ft_isdigit(*redir))
	{
		fd_dst = 0;
		while (ft_isdigit(*redir) && fd_dst <= MAX_FD)
			fd_dst = fd_dst * 10 + *redir++ - '0';
		if (fd_dst >= MAX_FD)
			return (eprintf("error: bad file descriptor\n"));
	}
	if (ft_isdigit(*word))
	{
		fd_src = 0;
		while (ft_isdigit(*word) && fd_src <= MAX_FD)
			fd_src = fd_src * 10 + *word++ - '0';
		if (fd_src >= MAX_FD)
			return (eprintf("error: bad file descriptor\n"));
	}
	else if (ft_strcmp(word, "-") == 0)
	{
		close(fd_dst);
		return (0);
	}
	else
		return (eprintf("error: %s: ambiguous redirect\n", word));
	dup2(fd_src, fd_dst);
	return (0);
}

int		dup_out(t_tree *tree, char *redir, char *word)
{
	int		fd_src;
	int		fd_dst;

	fd_dst = 1;
	fd_src = 1;
	if (ft_isdigit(*redir))
	{
		fd_dst = 0;
		while (ft_isdigit(*redir) && fd_dst <= MAX_FD)
			fd_dst = fd_dst * 10 + *redir++ - '0';
		if (fd_dst >= MAX_FD)
			return (eprintf("error: bad file descriptor\n"));
	}
	if (ft_isdigit(*word))
	{
		fd_src = 0;
		while (ft_isdigit(*word) && fd_src <= MAX_FD)
			fd_src = fd_src * 10 + *word++ - '0';
		if (fd_src >= MAX_FD)
			return (eprintf("error: bad file descriptor\n"));
	}
	else if (ft_strcmp(word, "-") == 0)
	{
		close(fd_dst);
		return (0);
	}
	else
		return (eprintf("error: %s: ambiguous redirect\n", word));
	dup2(fd_src, fd_dst);
	return (0);
}

int		cmd_redirection(t_tree *tree)
{
	char	s[BUFF_SZ + 1];
	int		i;
	int		j;

	i = 1;
	while (i < tree->nchild)
	{
		if (tree->child[i]->type == T_REDIR)
		{
			if (i + 1 >= tree->nchild)
			{
				g_errno = E_TOKSYNTAX;
				eprintf("%s '%s'\n", g_error[g_errno], tree->child[i]->token->s);
				return (-1);
			}
			j = get_identifier(tree, i + 1, s);
			if (s[0] == '\0')
			{
				g_errno = E_TOKSYNTAX;
				eprintf("%s '%s'\n", g_error[g_errno], tree->child[i]->token->s);
				return (-1);
			}
			if (tree->child[i]->token->sym == S_REDIRIN)
				redir_in(tree, tree->child[i]->token->s, s);
			else if (tree->child[i]->token->sym == S_REDIROUT)
				redir_out(tree, tree->child[i]->token->s, s);
			else if (tree->child[i]->token->sym == S_APPENDOUT)
				append_out(tree, tree->child[i]->token->s, s);
			else if (tree->child[i]->token->sym == S_DUPIN)
				dup_in(tree, tree->child[i]->token->s, s);
			else if (tree->child[i]->token->sym == S_DUPOUT)
				dup_out(tree, tree->child[i]->token->s, s);
			{
				for (int k = i; k < j; k++)
				{
					tree->child[k]->type = T_NAME;
					tree->child[k]->token->sym = S_SEPARATOR;
				}
			}
			i = j;
		}
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
