/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:45:43 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 14:31:38 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H

# include "read_line.h"

void	movecurlr(t_line *l, int move);
void	movelr(t_line *l, int move);
void	movecur_backtoi(t_line *l);
void	moveup(t_line *l);
void	movedown(t_line *l);
void	moveupdown(t_line *l, int move);
void	moveword(t_line *l, int move);
void	move_homeend(t_line *l, int move);
void	movecur_last(t_line *l);

#endif
