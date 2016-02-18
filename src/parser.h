/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 10:41:47 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/18 11:51:05 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

/*
** TODO: faire 1 constante par parenthese/crochet/accolade
**       -> virer T_BRACE et creer 3
*/

# define MAX_FD 0xFF

enum				e_nodetype
{
	T_CMD = 0xFFFF + 1,
	T_NAME,
	T_REDIR,
	T_OPER,
	T_BRACE,
	T_PIPE,
	T_SEMICOL
};

typedef struct		s_tree
{
	enum e_nodetype	type;
	struct s_tree	*child[BUFF_SZ];
	int				nchild;
	t_token			*token;
	int				fd[MAX_FD + 1];
}					t_tree;

t_tree				*parser(t_token *token);
void				next_token(t_token *token, int *index);
t_tree				*factor(t_tree *tree, t_token *token, int *index);
t_tree				*command(t_tree *tree, t_token *token, int *index);
char				**tree_totab(t_tree *tree);
int					get_identifier(t_tree *tree, int i, char *s);
void				deltree(t_tree *tree);

#endif
