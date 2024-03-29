/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:14:19 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 12:04:57 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "ft_env.h"
# include "parser.h"

void	expand_brace(t_tree *tree, t_env *env);
void	expand_tilde(t_tree *tree, t_env *env);
void	expand_all(t_tree *tree, t_env *env);

#endif
