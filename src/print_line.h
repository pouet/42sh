/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:52:47 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 12:03:11 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_LINE_H
# define PRINT_LINE_H

# include "read_line.h"

int		print_line_initval(t_line *l, char *prompt);
void	print_line(t_line *l, char *prompt);
void	clrscr_down(t_line *l);
void	putprompt_lastline(char *prompt);

#endif
