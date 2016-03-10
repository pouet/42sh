/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 12:17:16 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 12:28:56 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CD_H
# define FT_CD_H

# include "ft_env.h"
# include "get_opts.h"

t_env	*ft_cd(t_env *env, t_tree *tree);
int		del_multipleslash(char *s, int len);
int		del_finalslash(char *s, int len);
int		del_dotslash(char *s, int len);
int		del_dotdot(char *s, int len);
char	*move_dotdot(char *s, char *t, int *len, int i);
int		set_cdenv(t_env *env, char *path, char *s, t_flags flags);
int		set_cdpath(t_env *env, char *path, char *s);
int		set_cdstring(t_env *env, char *s);
char	*get_nextid(char *s, char *name);
int		convert_canonical(char *s);
t_flags	get_cdflags(t_tree *tree, int *i);
int		changedir(char *path);

#endif
