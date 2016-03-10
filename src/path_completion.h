/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_completion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:35:56 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 14:37:14 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_COMPLETION_H
# define PATH_COMPLETION_H

# include "read_line.h"
# include "ft_env.h"
# include "lexer.h"

int		path_count(t_line *l, char *path, char *file, char *res);
int		path_complete(t_line *l, char *s, int len);
int		path_multiple(t_line *l, char *path, char *file);
void	path_expand(t_token *token, t_env *env, char *s, int len);
int		path_completion(t_line *l, t_env *env, char *s, int len);

#endif
