/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 12:07:18 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 08:46:02 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# include "libft.h"
# include "parser.h"
# include "hashtable.h"

typedef t_list	t_env;

t_env		*env_newelement(char *s);
t_env		*ft_env(t_env *env, t_tree *tree);
t_env		*create_env_environ(void);
t_env		*env_getname(t_env *env, char *name);
char		**env_totab(t_env *env);
t_hash		*hash_createfile(t_env *env);
t_hash		*hash_update(t_env *env);

#endif
