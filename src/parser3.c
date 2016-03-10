/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:02:17 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 14:03:43 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "lexer.h"
#include "error.h"

t_tree	*tree_new(enum e_nodetype type, t_token *token)
{
	t_tree	*node;

	node = ft_memalloc(sizeof(*node));
	node->type = type;
	node->token = token;
	return (node);
}

void	deltree(t_tree *tree)
{
	int	i;

	if (tree)
	{
		i = 0;
		while (i < tree->nchild)
		{
			deltree(tree->child[i]);
			i++;
		}
		free(tree);
	}
}

void	next_token(t_token *token, int *index)
{
	if (token[*index].sym != S_EOL)
		(*index)++;
}

int		found(t_token *token, int *index, t_symbol symbol)
{
	if (token[*index].sym == symbol)
		return (1);
	return (0);
}

int		accept(t_token *token, int *index, t_symbol symbol)
{
	if (found(token, index, symbol))
	{
		next_token(token, index);
		return (1);
	}
	return (0);
}
