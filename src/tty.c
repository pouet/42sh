/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 08:48:37 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/26 11:17:52 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "tty.h"
#include "error.h"

static int fd_stdin;

int		set_tty_fd(void)
{
	char	*tty;
	int		fd;

	tty = ttyname(0);
	if (tty == NULL)
		return (eprintf("error: failed to get tty name\n"));
	fd = open(tty, O_RDWR);
	if (fd < 0)
		return (eprintf("error: failed to open tty\n"));
	fd_stdin = dup(0);
	if (dup2(fd, 0) < 0)
		return (eprintf("error: failed to dup tty\n"));
	return (0);
}

void	close_tty_fd(void)
{
//	close(0);
	dup2(fd_stdin, 0);
}
