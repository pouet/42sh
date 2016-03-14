/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 12:04:53 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/27 08:54:58 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# define CLRSCR "cl"
# define MVCUR "cm"
# define SRVIDEO "mr"
# define URVIDEO "se"
# define SUNDERL "us"
# define UUNDERL "ue"
# define SKEYPAD "ks"
# define UKEYPAD "ke"
# define CURINVI "vi"
# define CURVI "ve"

# define TXT_NORM (0x0)
# define TXT_RVID (0x1 << 0)
# define TXT_UDRL (0x1 << 1)

int		ft_putchar_tty(int c);
void	ft_tputs(char *s);
void	clr_screen(void);
void	mv_cur(char *cap, int hpos, int vpos);
void	print_txt(char *s, int hpos, int vpos, unsigned type);

#endif
