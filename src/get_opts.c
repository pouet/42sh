/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 11:04:14 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/11 09:12:44 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "get_opts.h"
#include "error.h"

char	*get_opts(char *s, char *opts, t_flags *val_opts, t_flags *flags)
{
	char	*p;

	if (*s != '-')
		return (s);
	s++;
	while (*s)
	{
		p = ft_strchr(opts, *s);
		if (p == NULL)
			return (s);
		*flags |= val_opts[p - opts];
		s++;
	}
	return (s);
}
