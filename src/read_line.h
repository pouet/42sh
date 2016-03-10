/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 10:33:59 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 11:09:49 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_LINE_H
# define READ_LINE_H

# include "ft_env.h"

typedef struct	s_line
{
	char			*s;
	int				i;
	int				len;
	int				lenmax;
	int				lenprompt;
	int				col;
	int				row;
	int				oldcol;
	int				oldrow;
	int				wincol;
	int				winrow;
	int				curcol;
	int				currow;
}				t_line;

typedef struct		s_history
{
	t_dllist		*dll;
	t_node			*cur;
	t_node			*new;
}					t_history;

char				*read_line(char *prompt, t_history *h, t_env *env,
		int *sig);
t_line				*growup_line(t_line *l);
char				*add_char(t_line *l, char c);

#endif
