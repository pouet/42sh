/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:51:17 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 11:54:04 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_line.h"
#include "read_line.h"
#include "move.h"
#include "print.h"

int		print_line_initval(t_line *l, char *prompt)
{
	if (l->s == NULL)
		return (-1);
	l->oldrow = l->row;
	l->oldcol = l->col;
	putprompt_lastline(prompt);
	l->col = l->lenprompt;
	l->row = 0;
	return (0);
}

void	print_line(t_line *l, char *prompt)
{
	int		i;

	if (print_line_initval(l, prompt) < 0)
		return ;
	i = 0;
	while (i < l->len)
	{
		ft_putchar(l->s[i]);
		if (l->s[i] == '\n')
		{
			l->row++;
			l->col = 0;
		}
		else
			l->col++;
		if (l->col >= l->wincol)
		{
			l->row++;
			l->col = 0;
		}
		i++;
	}
	if (l->col == 0)
		ft_putchar(' ');
	movecur_backtoi(l);
}

void	clrscr_down(t_line *l)
{
	if (l->currow > 0)
		mv_cur("UP", 0, l->currow);
	ft_tputs("cr");
	ft_tputs("cd");
}

void	putprompt_lastline(char *prompt)
{
	int		len;

	len = ft_strlen(prompt);
	while (len > 0 && prompt[len] != '\n')
		len--;
	if (prompt[len] == '\n')
		len++;
	ft_putstr(prompt + len);
}
