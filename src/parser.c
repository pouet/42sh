/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 10:41:37 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 15:32:59 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "lexer.h"
#include "error.h"
#include "xmalloc.h"

t_tree	*identifiers(t_tree *tree, t_token *token, int *index)
{
	t_tree	*node;

	if (token_isstring(token, index))
	{
		node = tree_new(T_CMD, NULL);
		if (tree == NULL)
			tree = node;
		else
			node->child[node->nchild++] = tree;
		tree = node;
		while (token_isstring(token, index) || found(token, index, S_EQUAL)
			|| found(token, index, S_SEPARATOR) || token_isredir(token, index))
		{
			if (token_isredir(token, index))
				tree->child[tree->nchild++] = tree_new(T_REDIR, token + *index);
			else
				tree->child[tree->nchild++] = tree_new(T_NAME, token + *index);
			next_token(token, index);
		}
//		tree = command(tree, token, index);
	}
	return (tree);
}

/*
** while (found(token, index, S_LHOOK) || found(token, index, S_LBRACE)
**		|| found(token, index, S_LPAR))
**	tree = factor(tree, token, index);
*/

t_tree	*command(t_tree *tree, t_token *token, int *index)
{
	while (accept(token, index, S_SEPARATOR))
		;
	tree = identifiers(tree, token, index);
	while (accept(token, index, S_SEPARATOR))
		;
	tree = pipetree(tree, token, index);
	while (accept(token, index, S_SEPARATOR))
		;
	tree = semicolon(tree, token, index);
	return (tree);
}

t_tree	*parser(t_token *token)
{
	t_tree	*tree;
	int		index;

	g_errno = E_NOERROR;
	index = 0;
	tree = NULL;
	tree = command(tree, token, &index);
	if (g_errno)
	{
		deltree(tree);
		return (NULL);
	}
	if (!found(token, &index, S_EOL))
	{
		deltree(tree);
		eprintf("syntax error near unexpected token '%s'\n", token[index].s);
		return (NULL);
	}
	return (tree);
}

char	**tree_totab(t_tree *tree)
{
	int		i;
	int		j;
	char	**tab;

	tab = xmalloc((BUFF_SZ + 1) * sizeof(*tab));
	i = 0;
	j = 0;
	while (j < tree->nchild)
	{
		tab[i] = ft_memalloc((BUFF_SZ + 1) * sizeof(**tab));
		while (j < tree->nchild && tree->child[j]->token->sym == S_SEPARATOR)
			j++;
		if (j >= tree->nchild)
			break ;
		while (j < tree->nchild &&
				(tree->child[j]->token->sym == S_IDENT ||
				tree->child[j]->token->sym == S_EQUAL ||
				tree->child[j]->token->sym == S_COMMAND))
			ft_strlcat(tab[i], tree->child[j++]->token->s, BUFF_SZ);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int		get_identifier(t_tree *tree, int i, char *s)
{
	s[0] = '\0';
	while (i < tree->nchild && tree->child[i]->token->sym == S_SEPARATOR)
		i++;
	while (i < tree->nchild && (tree->child[i]->token->sym == S_IDENT ||
				tree->child[i]->token->sym == S_EQUAL))
		ft_strlcat(s, tree->child[i++]->token->s, BUFF_SZ);
	return (i);
}
