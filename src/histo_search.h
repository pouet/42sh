/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo_search.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 17:57:32 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/21 17:59:33 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTO_SEARCH_H
# define HISTO_SEARCH_H

# include "read_line.h"
# include "events.h"

void		replace_str(t_line *l, char *s);
void		histo_search(t_line *l, t_history *h, t_events *ev);

#endif
