/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 11:52:07 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/21 16:24:07 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

enum
{
	K_NONE,
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_DEL,
	K_BCKSP,
	K_ESCAP,
	K_CTRLD,
	K_CTRLR,
	K_ALTLFT,
	K_ALTRGT,
	K_ALTUP,
	K_ALTDWN,
	K_ALTA,
	K_ALTS,
	K_ALTD,
	K_ALTZ,
	K_ALTX,
	K_ALTC,
	K_ALTV,
	K_HOME,
	K_END,
	K_NKEYS
};

enum
{
	T_ALPHA,
	T_KEYS,
	T_OTHER
};

typedef struct	s_events
{
	int			type;
	int			c;
}				t_events;

int				getevents(t_events *ev);
int				keyisarrow(t_events *ev);

#endif
