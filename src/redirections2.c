/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:08:28 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 14:14:08 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/syslimits.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <limits.h>
#include "libft.h"
#include "redirections.h"
#include "lexer.h"
#include "parser.h"
#include "error.h"
#include "read_line.h"
#include "initterms.h"

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

int			redir(t_symbol sym, char *redir, char *word)
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

int			dup_fd(t_symbol sym, char *redir, char *word)
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

char		*join_heredoc(char *s, char *t)
{
	char	*tmp;

	tmp = ft_strjoin(s, t);
	free(t);
	free(s);
	s = ft_strjoin(tmp, "\n");
	free(tmp);
	return (s);
}

int			heredoc(t_symbol sym, char *redir, char *word)
{
	int		fd[2];
	char	*s;
	char	*t;

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
		s = join_heredoc(s, t);
	}
	unset_terms();
	pipe(fd);
	write(fd[1], s, ft_strlen(s));
	free(s);
	signal(SIGINT, SIG_IGN);
	return (close(fd[1]) < 0 || dup2(fd[0], 0) < 0 || close(fd[0]) < 0);
}
