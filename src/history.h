/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 14:55:07 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 08:54:08 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "libft.h"
# include "read_line.h"

# define HISTORY_FILE ".42sh_history"

void	histo_load(t_history *h);
int		histo_add(t_history *h, char *s);
int		histo_up(t_history *h, t_line *l);
int		histo_down(t_history *h, t_line *l);

#endif
