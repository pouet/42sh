/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 08:48:37 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/27 09:35:40 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "tty.h"

int		*tty_ptr(void)
{
	static int		fd = -2;

	return (&fd);
}

int		get_tty_fd(void)
{
	int		*fd;

	fd = tty_ptr();
	if (*fd == -2)
		*fd = open("/dev/tty", O_RDWR);
	if (*fd < 0)
	{
		ft_putstr_fd("failed to open tty\n", 2);
		exit(1);
	}
	return (*fd);
}

void	close_tty_fd(void)
{
	int		*fd;

	fd = tty_ptr();
	close(*fd);
	*fd = -2;
}
