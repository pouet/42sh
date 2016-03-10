/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_restore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:18:15 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 15:21:39 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "save_restore.h"

void	save_stdfd(int fd[3])
{
	fd[0] = dup(0);
	fd[1] = dup(1);
	fd[2] = dup(2);
}

void	restore_stdfd(int fd[3])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	dup2(fd[2], 2);
}

void	restore_sigdfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}
