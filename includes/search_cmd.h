/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:26:41 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 14:27:33 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCH_CMD_H
# define SEARCH_CMD_H

# include "lexer.h"
# include "ft_env.h"

int		is_builtin(char *s);
char	*create_path(char *file, char *path, char *s);
int		is_pathsearch(char *s, t_env *env);
int		find_cmd(t_token *token, t_env *env);

#endif
