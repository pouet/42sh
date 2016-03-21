/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:01:55 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/21 15:15:20 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "lexer.h"
#include "error.h"

int		token_isredir(t_token *token, int *index)
{
	if (found(token, index, S_HERESTR) || found(token, index, S_HEREDOC)
		|| found(token, index, S_APPENDOUT) || found(token, index, S_DUPIN)
		|| found(token, index, S_DUPOUT) || found(token, index, S_REDIRINOUT)
		|| found(token, index, S_REDIRIN) || found(token, index, S_REDIROUT))
		return (1);
	return (0);
}

int		token_isstring(t_token *token, int *index)
{
	if (found(token, index, S_IDENT) || found(token, index, S_DQUOTE)
		|| found(token, index, S_SQUOTE) || found(token, index, S_BACKQUOTE))
		return (1);
	return (0);
}

t_tree	*factor(t_tree *tree, t_token *token, int *index)
{
	t_symbol	sym;
	t_tree		*node;

	if (accept(token, index, S_LHOOK))
		sym = S_RHOOK;
	else if (accept(token, index, S_LBRACE))
		sym = S_RBRACE;
	else if (accept(token, index, S_LPAR))
		sym = S_RPAR;
	else
		return (tree);
	node = tree_new(T_BRACE, NULL);
	if (tree == NULL)
		tree = node;
	else
		node->child[0] = tree;
	node->nchild = 2;
	node->child[1] = command(NULL, token, index);
	if (!accept(token, index, sym))
	{
		g_errno = E_MISSBRACE;
		eprintf("error: missing close brace\n");
		return (node);
	}
	return (node);
}

t_tree	*semicolon(t_tree *tree, t_token *token, int *index)
{
	t_tree	*node;

	if (accept(token, index, S_SEMICOL))
	{
		node = tree_new(T_SEMICOL, NULL);
		if (tree == NULL || tree->type == T_REDIR || tree->type == T_NAME)
		{
			g_errno = E_SYNTAX;
			eprintf("syntax error near unexpexted token ';'\n");
			return (tree);
		}
		else
			node->child[0] = tree;
		tree = node;
		tree->child[1] = command(tree->child[1], token, index);
		tree->nchild = 2;
	}
	return (tree);
}

t_tree	*pipetree(t_tree *tree, t_token *token, int *index)
{
	t_tree	*node;

	if (accept(token, index, S_PIPE))
	{
		node = tree_new(T_PIPE, NULL);
		if (tree == NULL || tree->type != T_CMD)
		{
			g_errno = E_SYNTAX;
			eprintf("syntax error near unexpexted token '|'\n");
			return (tree);
		}
		else
			node->child[0] = tree;
		tree = node;
		tree->child[1] = pipe_command(tree->child[1], token, index);
		if (tree->child[1] == NULL)
		{
			g_errno = E_SYNTAX;
			eprintf("syntax error near unexpexted token '|'\n");
			return (tree);
		}
		node->nchild = 2;
	}
	return (tree);
}
