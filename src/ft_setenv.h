/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 11:41:22 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/05 12:24:24 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SETENV_H
# define FT_SETENV_H

# include "ft_setenv.h"
# include "ft_env.h"
# include "parser.h"

t_env	*ft_setenv(t_env *env, t_tree *tree);
t_env	*ft_setenv_byname(t_env *env, char *name_value);
t_env	*ft_unsetenv(t_env *env, t_tree *tree);
t_env	*ft_unsetenv_byname(t_env *env, char *name);

#endif
