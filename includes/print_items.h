/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_items.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 12:01:26 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/25 12:20:08 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_ITEMS_H
# define PRINT_ITEMS_H

# include "libft.h"
# include "context.h"

void	setcolor_byext(char *name);
void	print_one(t_context *cont, t_node *n, int co, int li);
void	print_items(t_context *cont);
void	print_cont(t_context *cont);
void	print_choice(t_dllist *l);

#endif
