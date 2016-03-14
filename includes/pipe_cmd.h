/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:23:26 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 14:24:17 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_CMD_H
# define PIPE_CMD_H

# include "ft_env.h"
# include "parser.h"

void	child_pipe(t_tree *tree, t_env *env, t_env *new, int fd_pipe[2]);
int		do_pipe(t_tree *tree, t_env *env, t_env *new);

#endif
