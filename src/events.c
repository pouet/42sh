/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 11:40:21 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 08:45:31 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <unistd.h>
#include "libft.h"
#include "events.h"
#include "print.h"

static void	set_keys(char **keys)
{
	keys[K_UP] = tgetstr("ku", NULL);
	keys[K_DOWN] = tgetstr("kd", NULL);
	keys[K_LEFT] = tgetstr("kl", NULL);
	keys[K_RIGHT] = tgetstr("kr", NULL);
	keys[K_DEL] = tgetstr("kD", NULL);
	keys[K_BCKSP] = "\x7f";
	keys[K_ESCAP] = "\x1b";
	keys[K_CTRLD] = "\x04";
	keys[K_CTRLR] = "\x12";
	keys[K_ALTUP] = "\x1b\x1b\x5b\x41";
	keys[K_ALTDWN] = "\x1b\x1b\x5b\x42";
	keys[K_ALTRGT] = "\x1b\x1b\x5b\x43";
	keys[K_ALTLFT] = "\x1b\x1b\x5b\x44";
	keys[K_ALTA] = "\xc3\xa5";
	keys[K_ALTS] = "\xc3\x9f";
	keys[K_ALTD] = "\xe2\x88\x82";
	keys[K_ALTZ] = "\xce\xa9";
	keys[K_ALTX] = "\xe2\x89\x88";
	keys[K_ALTC] = "\xc3\xa7";
	keys[K_ALTV] = "\xe2\x88\x9a";
	keys[K_HOME] = "\x1b\x4f\x48";
	keys[K_END] = "\x1b\x4f\x46";
}

static int	iskey(t_events *ev, char *buf, char *keys[])
{
	int			i;

	i = 0;
	while (i < K_NKEYS)
	{
		if (ft_strcmp(buf, keys[i]) == 0)
		{
			ev->type = T_KEYS;
			ev->c = i;
			return (1);
		}
		i++;
	}
	return (0);
}

int			getevents(t_events *ev)
{
	static char	*keys[K_NKEYS];
	char		buf[10];
	int			ret;

	bzero(buf, 10);
	ret = read(0, buf, 9);
	if (ret <= 0)
		return (ret);
	buf[ret] = '\0';
	ev->type = T_OTHER;
	if (keys[0] == NULL)
		set_keys(keys);
	if (iskey(ev, buf, keys))
		return (1);
	if (ret == 1 && (ft_isprint(buf[0]) || buf[0] == '\n' || buf[0] == '\t'))
	{
		ev->type = T_ALPHA;
		ev->c = buf[0];
	}
	return (1);
}

int			keyisarrow(t_events *ev)
{
	return (ev->c == K_UP || ev->c == K_DOWN || ev->c == K_LEFT
			|| ev->c == K_RIGHT);
}
