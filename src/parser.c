/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 10:41:37 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/18 11:51:11 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "lexer.h"
#include "error.h"

t_tree	*tree_new(enum e_nodetype type, t_token *token)
{
	t_tree	*node;
	int		i;

	node = ft_memalloc(sizeof(*node));
	node->type = type;
	node->fd[0] = 0;
	node->fd[1] = 1;
	node->fd[2] = 2;
	i = 3;
	while (i < MAX_FD)
	{
		node->fd[i] = -1;
		i++;
	}
	node->token = token;
	return (node);
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
		eprintf("error: missing close brace\n");
	return (node);
}

t_tree	*semicolon(t_tree *tree, t_token *token, int *index)
{
	t_tree	*node;

	if (accept(token, index, S_SEMICOL))
	{
		node = tree_new(T_SEMICOL, NULL);
		if (tree == NULL || tree->type != T_CMD)
		{
			g_errno = E_TOKSYNTAX;
			eprintf("syntax error near unexpexted token ';'\n");
		}
		else
			node->child[0] = tree;
		tree = node;
		tree->child[1] = command(tree->child[1], token, index);
		node->nchild = 2;
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
			g_errno = E_TOKSYNTAX;
			eprintf("syntax error near unexpexted token '|'\n");
		}
		else
			node->child[0] = tree;
		tree = node;
		tree->child[1] = command(tree->child[1], token, index);
//		if (tree->child[1] && tree->child[1]->type != T_CMD)
//			eprintf("%#x: ", tree->child[1]->type), eprintf("syntax error near unexpexted token '|'\n");
		node->nchild = 2;
	}
	return (tree);
}

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
		tree = command(tree, token, index);
	}
	return (tree);
}

t_tree	*command(t_tree *tree, t_token *token, int *index)
{
	t_tree	*node;

	while (found(token, index, S_LHOOK) || found(token, index, S_LBRACE)
			|| found(token, index, S_LPAR))
		tree = factor(tree, token, index);
	while (accept(token, index, S_SEPARATOR))
		;
	tree = identifiers(tree, token, index);
	tree = pipetree(tree, token, index);
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
		/* TODO: tout free */
		return (NULL);
	if (!found(token, &index, S_EOL))
	{
		eprintf("syntax error near unexpected token '%s'\n", token[index].s);
		/* TODO: tout free */
		return (NULL);
	}
	return (tree);
}

char	**tree_totab(t_tree *tree)
{
	int		i;
	int		j;
	char	**tab;

	tab = malloc((BUFF_SZ + 1) * sizeof(*tab));
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
