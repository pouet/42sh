/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 09:14:46 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/25 12:20:01 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLL_H
# define DLL_H

# include "libft.h"

# define BUFF_SZ 1024

typedef struct		s_choice
{
	char			name[BUFF_SZ + 1];
	int				len;
	int				select;
}					t_choice;

int					max_len(t_dllist *l);
t_node				*dll_next(t_node *cur, int inc);
t_node				*dll_move(t_dllist *l, t_node *cur, int n, int *index);

#endif
