/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 16:13:34 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/22 16:25:51 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "colors.h"

void	col_set(char *txt, char *underl, char *back)
{
	if (txt)
		ft_putstr(txt);
	if (underl)
		ft_putstr(underl);
	if (back)
		ft_putstr(back);
}

void	col_reset(void)
{
	ft_putstr(TXTRST);
}

void	col_putstr_tty(char *s, char *txt, char *underl, char *bck)
{
	if (txt)
		ft_putstr_fd(txt, 1);
	if (underl)
		ft_putstr_fd(underl, 1);
	if (bck)
		ft_putstr_fd(bck, 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd(TXTRST, 1);
}
