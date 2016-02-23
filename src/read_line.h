/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 10:33:59 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/23 11:20:25 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_LINE_H
# define READ_LINE_H

typedef struct	s_line
{
	char		*s;
	int			i;
	int			len;
	int			lenmax;
//	int			col;
//	int			lig;
}				t_line;

char	*read_line(int history);

#endif
