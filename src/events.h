/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 11:52:07 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/23 15:51:00 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

enum
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_DEL,
//	K_ENTER,
	K_BCKSP,
	K_ESCAP,
	K_CTRLD,
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
int				keyisarrow(t_events *ev);

#endif
