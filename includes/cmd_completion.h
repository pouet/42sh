/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_completion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:33:00 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 14:34:51 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_COMPLETION_H
# define CMD_COMPLETION_H

# include "read_line.h"
# include "hashtable.h"
# include "ft_env.h"

int		cmd_count(t_hash *hash, char *s, int len);
int		cmd_lenmax(t_hash *hash, int ncmd);
void	print_cmd(t_line *l, t_hash *hash, int ncmd, int lenmax);
int		cmd_multiple(t_line *l, t_hash *hash, int ncmd);
int		cmd_completion(t_line *l, t_env *env, char *s, int len);

#endif
