/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addchar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:01:06 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 12:02:55 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADDCHAR_H
# define ADDCHAR_H

# include "read_line.h"

char	*add_char(t_line *l, char c);
void	delchar(t_line *l, int move);

#endif
