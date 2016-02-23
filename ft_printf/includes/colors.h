/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 16:00:40 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/23 08:41:08 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define TXTBLK "\e[0;30m"
# define TXTRED "\e[0;31m"
# define TXTGRN "\e[0;32m"
# define TXTYLW "\e[0;33m"
# define TXTBLU "\e[0;34m"
# define TXTPUR "\e[0;35m"
# define TXTCYN "\e[0;36m"
# define TXTWHT "\e[0;37m"
# define BLDBLK "\e[1;30m"
# define BLDRED "\e[1;31m"
# define BLDGRN "\e[1;32m"
# define BLDYLW "\e[1;33m"
# define BLDBLU "\e[1;34m"
# define BLDPUR "\e[1;35m"
# define BLDCYN "\e[1;36m"
# define BLDWHT "\e[1;37m"
# define UNKBLK "\e[4;30m"
# define UNDRED "\e[4;31m"
# define UNDGRN "\e[4;32m"
# define UNDYLW "\e[4;33m"
# define UNDBLU "\e[4;34m"
# define UNDPUR "\e[4;35m"
# define UNDCYN "\e[4;36m"
# define UNDWHT "\e[4;37m"
# define BAKBLK "\e[40m"
# define BAKRED "\e[41m"
# define BAKGRN "\e[42m"
# define BAKYLW "\e[43m"
# define BAKBLU "\e[44m"
# define BAKPUR "\e[45m"
# define BAKCYN "\e[46m"
# define BAKWHT "\e[47m"
# define TXTRST "\e[0m"
# define N_COL 33

typedef struct	s_colors
{
	const char	*s;
	int			len;
	const char	*col;
}				t_colors;

void			prtf_col_set(char *txt, char *back);
void			prtf_col_reset(void);
void			prtf_col_putstr(char *s, char *txt, char *back);
void			prtf_col_putendl(char *s, char *txt, char *back);
int				prtf_color_args(const char **fmt);

#endif
