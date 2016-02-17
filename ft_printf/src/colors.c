/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 16:13:34 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/04 08:51:33 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "colors.h"
#include "fd.h"

t_colors	g_colors[N_COL] = {
	{ "{black}", 7, TXTBLK },
	{ "{red}", 5, TXTRED },
	{ "{green}", 7, TXTGRN },
	{ "{yellow}", 8, TXTYLW },
	{ "{blue}", 6, TXTBLU },
	{ "{purple}", 8, TXTPUR },
	{ "{cyan}", 6, TXTCYN },
	{ "{white}", 7, TXTWHT },
	{ "{bld_black}", 11, BLDBLK },
	{ "{bld_red}", 9, BLDRED },
	{ "{bld_green}", 11, BLDGRN },
	{ "{bld_yellow}", 12, BLDYLW },
	{ "{bld_blue}", 10, BLDBLU },
	{ "{bld_purple}", 12, BLDPUR },
	{ "{bld_cyan}", 10, BLDCYN },
	{ "{bld_white}", 11, BLDWHT },
	{ "{under_black}", 13, UNKBLK },
	{ "{under_red}", 11, UNDRED },
	{ "{under_green}", 13, UNDGRN },
	{ "{under_yellow}", 14, UNDYLW },
	{ "{under_blue}", 12, UNDBLU },
	{ "{under_purple}", 14, UNDPUR },
	{ "{under_cyan}", 12, UNDCYN },
	{ "{under_white}", 13, UNDWHT },
	{ "{back_black}", 12, BAKBLK },
	{ "{back_red}", 10, BAKRED },
	{ "{back_green}", 12, BAKGRN },
	{ "{back_yellow}", 13, BAKYLW },
	{ "{back_blue}", 11, BAKBLU },
	{ "{back_purple}", 13, BAKPUR },
	{ "{back_cyan}", 11, BAKCYN },
	{ "{back_white}", 12, BAKWHT },
	{ "{eoc}", 5, TXTRST },
};

void	col_set(char *txt, char *back)
{
	if (txt)
		ft_putstr_fd(txt, get_fd());
	if (back)
		ft_putstr_fd(back, get_fd());
}

void	col_reset(void)
{
	ft_putstr_fd(TXTRST, get_fd());
}

void	col_putstr(char *s, char *txt, char *back)
{
	col_set(txt, back);
	ft_putstr_fd(s, get_fd());
	col_reset();
}

void	col_putendl(char *s, char *txt, char *back)
{
	col_putstr(s, txt, back);
	ft_putendl("");
}

int		color_args(const char **fmt)
{
	int		i;

	i = 0;
	while (i < N_COL)
	{
		if (ft_strncmp(*fmt, g_colors[i].s, g_colors[i].len) == 0)
		{
			ft_putstr_fd(g_colors[i].col, get_fd());
			(*fmt) += g_colors[i].len;
			break ;
		}
		i++;
	}
	if (i == N_COL)
	{
		ft_putchar(**fmt);
		(*fmt)++;
		return (1);
	}
	return (0);
}
