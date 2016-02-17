/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 09:10:06 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/08 08:59:26 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (del == NULL || alst == NULL || *alst == NULL)
		return (-1);
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
	return (0);
}
