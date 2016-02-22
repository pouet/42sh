/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 09:06:11 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/26 11:03:32 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include <sys/ioctl.h>
# include <time.h>
# include "libft.h"
# include "dll.h"

typedef struct		s_search
{
	char			word[BUFF_SZ + 1];
	clock_t			old;
	int				found;
}					t_search;

typedef struct		s_context
{
	struct winsize	ws;
	int				li;
	int				co;
	t_dllist		*l;
	t_node			*cur;
	int				ncur;
	int				nprev;
	t_search		srch;
}					t_context;

int					init_context(t_context *cont, int ac, char **av);
void				selchoice(t_context *cont);
void				delchoice(t_context *cont);

#endif
