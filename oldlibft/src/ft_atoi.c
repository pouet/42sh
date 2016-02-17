/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 08:50:07 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/02 12:55:46 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *nptr)
{
	long long	n;
	int			sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		nptr++;
		sign = -sign;
	}
	while (ft_isdigit(*nptr))
	{
		n = (n * 10) + (*nptr - '0');
		nptr++;
	}
	return ((int)(sign * n));
}
