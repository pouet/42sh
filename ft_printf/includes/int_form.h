/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_form.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:27:32 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/07 11:40:21 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_FORM_H
# define INT_FORM_H

# include <stdarg.h>
# include "subfmt.h"
# include "int_args.h"

void	set_sign(int *len, char *form, unsigned mod, unsigned long long *n);
int		get_int_sign(char c, char *form, unsigned mod, unsigned long long *n);
int		ull_to_str(char *s, unsigned long long n, char c);
int		set_int_form(char *form, char fmt, t_fmtspec *sp, int n);
void	calc_len_space(t_fmtspec *sp, t_text *t, int *lenzero, int *lenspace);

#endif
