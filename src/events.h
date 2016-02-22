/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 11:52:07 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/22 16:09:54 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "context.h"

enum
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_DEL,
	K_ENTER,
	K_BCKSP,
	K_ESCAP,
	K_SPACE,
	K_HOME,
	K_END,
	K_NKEYS
};

enum
{
	T_ALPHA,
	T_KEYS
};

typedef struct	s_events
{
	int			type;
	int			c;
}				t_events;

int				getevents(t_events *ev);
void			move_key(t_context *cont, t_events *ev);
int				keyisarrow(t_events *ev);

#endif
