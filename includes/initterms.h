/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initterms.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 11:59:39 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/25 15:02:15 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITTERMS_H
# define INITTERMS_H

# include <term.h>

int		init_term(void);
void	set_extern_var(void);
void	set_terms(void);
void	unset_terms(void);

#endif
