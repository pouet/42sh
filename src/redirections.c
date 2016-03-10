/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 11:06:05 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 11:42:51 by nchrupal         ###   ########.fr       */
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

int		redir(t_symbol sym, char *redir, char *word)
{
	int		fd;
	int		fd_src;
	char	*tmp;

	fd = 0;
	tmp = redir;
	fd_src = get_nbr(tmp, &redir);
	if (tmp == redir)
		fd_src = (sym != S_REDIRIN);
	if ((*redir != '>' && *redir != '<') || fd_src >= OPEN_MAX)
		return (eprintf("error: %s: %s\n", redir, g_error[E_BADFD]));
	if (sym == S_REDIRIN)
		fd = open(word, O_RDONLY);
	else if (sym == S_REDIROUT)
		fd = open(word, O_WRONLY | O_CREAT | O_TRUNC,
				S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	else if (sym == S_APPENDOUT)
		fd = open(word, O_WRONLY | O_CREAT | O_APPEND,
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (eprintf("error: %s: unable to open the file\n", redir));
	dup2(fd, fd_src);
	return (0);
}

int		dup_fd(t_symbol sym, char *redir, char *word)
{
	int		fd_src;
	int		fd_dst;
	char	*tmp;

	tmp = redir;
	fd_dst = get_nbr(tmp, &redir);
	if (tmp == redir)
		fd_dst = (sym != S_DUPIN);
	if ((*redir != '>' && *redir != '<') || fd_dst >= OPEN_MAX)
		return (eprintf("error: %s: %s\n", redir, g_error[E_BADFD]));
	tmp = word;
	fd_src = get_nbr(tmp, &word);
	if (tmp == word)
		fd_src = (sym != S_DUPIN);
	if ((*word != '\0' && *word != '-') || fd_src >= OPEN_MAX)
		return (eprintf("error: %s: %s\n", word, g_error[E_BADFD]));
	else if (ft_strcmp(word, "-") == 0)
		return (close(fd_dst));
	dup2(fd_src, fd_dst);
	return (0);
}

#include <sys/ioctl.h>
#include <signal.h>

static int	g_sigint_line;

static void	sigint_line(int sig)
{
	char	c;

	(void)sig;
	c = '\n';
	g_sigint_line = 1;
	ioctl(0, TIOCSTI, &c);
	signal(SIGINT, SIG_IGN);
}

int		heredoc(t_symbol sym, char *redir, char *word)
{
	int		fd[2];
	char	*s;
	char	*t;
	char	*tmp;

	set_terms();
	(void)sym;
	(void)redir;
	s = ft_strnew(1);
	signal(SIGINT, sigint_line);
	g_sigint_line = 0;
	while (1)
	{
		t = read_line(">> ", NULL, NULL, &g_sigint_line);
		if (t == NULL || ft_strcmp(t, word) == 0)
			break ;
		tmp = ft_strjoin(s, t);
		free(t);
		free(s);
		s = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	unset_terms();
	pipe(fd);
	write(fd[1], s, ft_strlen(s));
	free(s);
	signal(SIGINT, SIG_IGN);
	return (close(fd[1]) < 0 || dup2(fd[0], 0) < 0 || close(fd[0]) < 0);
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
