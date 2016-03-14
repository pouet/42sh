/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:29:30 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/02 11:10:27 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_CMD_H
# define PROCESS_CMD_H

# include "parser.h"
# include "ft_env.h"
# include "lexer.h"

typedef t_env *(*t_builtinfct)(t_env *, t_tree *);

typedef struct			s_builtinlist
{
	char				*name;
	t_builtinfct		f;
}						t_builtinlist;

# define NBUILTIN 5

extern t_builtinlist	g_bt[NBUILTIN];

int						process_cmd(t_tree *tree, t_env *env, t_env *new);
char					*create_path(char *file, char *path, char *s);

#endif
