/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:29:30 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/10 15:20:44 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_CMD_H
# define PROCESS_CMD_H

# include "parser.h"
# include "ft_env.h"
# include "parser.h"
# include "lexer.h"

typedef struct
{
	char	*name;
	t_env	*(*f)(t_env *, t_tree *);
}			t_builtinlist;

#define NBUILTIN 5

extern t_builtinlist bt[NBUILTIN];

int		process_cmd(t_tree *tree, t_env *env, t_env *new);

#endif
