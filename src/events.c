/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 11:40:21 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/23 11:53:44 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <unistd.h>
#include "libft.h"
#include "events.h"

static void	set_keys(char **keys)
{
	keys[K_UP] = tgetstr("ku", NULL);
	keys[K_DOWN] = tgetstr("kd", NULL);
	keys[K_LEFT] = tgetstr("kl", NULL);
	keys[K_RIGHT] = tgetstr("kr", NULL);
	keys[K_DEL] = tgetstr("kD", NULL);
//	keys[K_ENTER] = "\n";
	keys[K_BCKSP] = "\177";
	keys[K_ESCAP] = "\33";
//	keys[K_HOME] = tgetstr("kh", NULL);
//	keys[K_END] = tgetstr("kH", NULL);
}

int			getevents(t_events *ev)
{
	static char	*keys[K_NKEYS];
	int			i;
	char		buf[10];
	int			ret;

	ret = read(0, buf, 9);
	if (ret <= 0)
		return (ret);
	buf[ret] = '\0';
	if (keys[0] == NULL)
		set_keys(keys);
	i = 0;
	while (i < K_NKEYS)
	{
		if (keys[i] == NULL)
			printf("keys[%d]: NULL\n", i);
		if (ft_strcmp(buf, keys[i]) == 0)
		{
			ev->type = T_KEYS;
			ev->c = i;
			return (1);
		}
		i++;
	}
	ev->type = T_ALPHA;
	ev->c = buf[0];
	return (ret == 1/* && ft_isprint(buf[0])*/);
}

int			keyisarrow(t_events *ev)
{
	return (ev->c == K_UP || ev->c == K_DOWN || ev->c == K_LEFT
			|| ev->c == K_RIGHT);
}
