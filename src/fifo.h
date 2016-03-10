/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:28:29 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 11:38:59 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIFO_H
# define FIFO_H

# include "lexer.h"

typedef struct			s_fifo
{
	char				t[BUFF_SZ + 1];
	int					i;
}						t_fifo;

extern const char		*g_corr;

int						fifo_push(t_fifo *fifo, char c);
char					fifo_pop(t_fifo *fifo);

#endif
