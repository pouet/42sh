/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 10:46:35 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/25 11:16:15 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIPBOARD_H
# define CLIPBOARD_H

#include "read_line.h"

enum e_clipboard
{
	C_CUTEND,
	C_CUTBEG,
	C_CUTALL,
	C_CPYEND,
	C_CPYBEG,
	C_CPYALL,
	C_PASTE
};

void	clip_cut(enum e_clipboard type, t_line *l);
void	clip_copy(enum e_clipboard type, t_line *l);
void	clip_paste(t_line *l);

#endif
