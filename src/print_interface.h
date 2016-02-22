/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 12:40:42 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/26 10:21:33 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_INTERFACE_H
# define PRINT_INTERFACE_H

# include "context.h"

void	print_edge(t_context *cont);
void	print_search(t_context *cont);
void	print_cmd(t_context *cont);
t_node	*print_arrows(t_context *cont, int maxco);

#endif
