/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:25:19 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 11:38:26 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETLINE_H
# define GETLINE_H

# include "read_line.h"
# include "history.h"
# include "fifo.h"

void		getbraces(char *s, t_fifo *fifo);
char		*addline(t_history *h, char *prompt, char *s, char *t);
char		*getline(t_history *h, t_env *env);

#endif
