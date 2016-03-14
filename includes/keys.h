/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:56:32 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 12:03:28 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# include "read_line.h"
# include "history.h"
# include "events.h"

void	clipboard_key(t_line *l, int move);
void	histo_key(t_history *h, t_line *l, int move);
int		key(t_line *l, t_history *h, t_events *ev);
void	tabulation(t_line *l, t_env *env, t_events *ev, char *prompt);
int		character(t_line *l, t_events *ev);

#endif
