/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 09:22:31 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/11 15:05:23 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstadd(t_list **alst, t_list *new)
{
	if (alst == NULL || new == NULL)
		return (-1);
	if (*alst != NULL)
		new->next = *alst;
	*alst = new;
	return (0);
}
