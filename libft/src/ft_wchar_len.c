/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:47:19 by nchrupal          #+#    #+#             */
/*   Updated: 2016/01/07 11:59:27 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_wchar_len(wchar_t c)
{
	if ((c & 0xFFFFFF00) == 0)
		return (1);
	else if ((c & 0xFFFFF000) == 0)
		return (2);
	else if ((c & 0xFFFF0000) == 0)
		return (3);
	else
		return (4);
}
