/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_newlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 11:29:25 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/20 11:29:47 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_dllist	*dll_newlist(void)
{
	t_dllist	*l;

	l = malloc(sizeof(*l));
	if (l == NULL)
		return (l);
	l->sz = 0;
	l->first = NULL;
	l->last = NULL;
	return (l);
}
