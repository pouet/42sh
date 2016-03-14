/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 08:29:23 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 14:38:21 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H

# include "ft_env.h"
# include "read_line.h"

int		completion(t_line *l, t_env *env);
int		is_firstword(t_line *l, char *s);
int		add_completion(t_line *l, char *s, int len);

#endif
