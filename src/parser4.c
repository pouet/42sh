/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:16:02 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/21 15:16:09 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "lexer.h"
#include "error.h"

t_tree	*pipe_command(t_tree *tree, t_token *token, int *index)
{
	while (accept(token, index, S_SEPARATOR))
		;
	tree = identifiers(tree, token, index);
	tree = pipetree(tree, token, index);
	return (tree);
}
