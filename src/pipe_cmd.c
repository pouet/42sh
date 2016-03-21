/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:21:48 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 15:21:45 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "error.h"
#include "process_cmd.h"
#include "ft_env.h"
#include "parser.h"

void	child_pipe(t_tree *tree, t_env *env, t_env *new, int fd_pipe[2])
{
	close(fd_pipe[0]);
	dup2(fd_pipe[1], 1);
	close(fd_pipe[1]);
	process_cmd(tree->child[0], env, new);
	exit(0);
}

int		do_pipe(t_tree *tree, t_env *env, t_env *new)
{
	int		fd_pipe[2];
	int		stat_loc;
	int		fd_sav;
	pid_t	pid;

	if (pipe(fd_pipe) < 0)
		return (eprintf("error: cannot create pipe\n"));
	if ((pid = fork()) < 0)
		return (eprintf("error: fork failed\n"));
	else if (pid == 0)
		child_pipe(tree, env, new, fd_pipe);
	else
	{
		fd_sav = dup(0);
		close(fd_pipe[1]);
		dup2(fd_pipe[0], 0);
		close(fd_pipe[0]);
		process_cmd(tree->child[1], env, new);
		dup2(fd_sav, 0);
		close(fd_sav);
		while (waitpid(pid, &stat_loc, WNOHANG) == 0)
			;
	}
	return (0);
}
