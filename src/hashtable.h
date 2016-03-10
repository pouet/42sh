/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:53:07 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 11:04:20 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include "lexer.h"

# define SZHASH 97

typedef struct		s_hash
{
	unsigned		key;
	char			cmd[BUFF_SZ + 1];
	char			fullpath[BUFF_SZ + 1];
	struct s_hash	*next;
}					t_hash;

t_hash				*hash_new(void);
void				hash_del(t_hash *hash);
unsigned			hash_key(char *cmd);
t_hash				*hash_exist(t_hash *hash, char *cmd);
t_hash				*hash_insert(t_hash *hash, char *cmd, char *fullpath);

#endif
