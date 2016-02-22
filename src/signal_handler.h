/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 09:01:39 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/26 11:05:08 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include "context.h"

typedef struct		s_sigvar
{
	struct termios	old;
	struct termios	new;
}					t_sigvar;

void				sig_handler(int sig);
void				sig_winch(int sig);
void				check_changews(t_context *cont);
void				set_signal(void);

#endif
