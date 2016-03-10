/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:24:01 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 11:39:33 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "getline.h"
#include "fifo.h"
#include "xmalloc.h"
#include "colors.h"

static int	g_sigint_line;

static void	sigint_line(int sig)
{
	char	c;

	(void)sig;
	c = '\n';
	g_sigint_line = 1;
	ioctl(0, TIOCSTI, &c);
	signal(SIGINT, SIG_IGN);
}

void		getprompt(char *s, unsigned len)
{
	time_t	t;
	char	*clock;
	char	pwd[BUFF_SZ + 1];

	s[0] = '\0';
	t = time(NULL);
	clock = ctime(&t);
	ft_strlcat(s, TXTPUR, len);
	ft_strlcat(s, clock, len);
	getcwd(pwd, BUFF_SZ);
	ft_strlcat(s, TXTGRN, len);
	ft_strlcat(s, pwd, len);
	ft_strlcat(s, TXTRST, len);
	ft_strlcat(s, " -> ", len);
}

void		getbraces(char *s, t_fifo *fifo)
{
	char	*t;
	int		index;

	while (s && *s)
	{
		t = ft_strchr(g_corr, *s);
		if (t != NULL)
		{
			index = t - g_corr;
			if (fifo->i > 0 && index < 6 && *s == fifo->t[fifo->i - 1])
				index++;
			if (index % 2 == 0 && (fifo->i == 0 || (fifo->i > 0 &&
				fifo->t[fifo->i - 1] != '"' && fifo->t[fifo->i - 1] != '\'' &&
				fifo->t[fifo->i] != '`')))
				fifo_push(fifo, g_corr[index]);
			else if (index % 2 == 1 && fifo->i > 0
					&& *s == fifo->t[fifo->i - 1])
				fifo_pop(fifo);
		}
		s++;
	}
}

char		*addline(t_history *h, char *prompt, char *s, char *t)
{
	char	*tmp;

	if (s == NULL)
	{
		s = t;
		histo_add(h, s);
		ft_strcpy(prompt, " > ");
	}
	else
	{
		tmp = xmalloc((ft_strlen(s) + ft_strlen(t) + 2) * sizeof(*tmp));
		ft_strcpy(tmp, s);
		ft_strcat(tmp, "\n");
		ft_strcat(tmp, t);
		free(s);
		free(t);
		s = tmp;
		free(h->dll->first->data);
		h->dll->first->data = ft_strdup(s);
	}
	return (s);
}

char		*getline(t_history *h, t_env *env)
{
	char	prompt[BUFF_SZ + 1];
	t_fifo	fifo;
	char	*s;
	char	*t;

	s = NULL;
	ft_bzero(&fifo, sizeof(fifo));
	getprompt(prompt, BUFF_SZ);
	signal(SIGINT, sigint_line);
	g_sigint_line = 0;
	while (g_sigint_line == 0 && (s == NULL || (s != NULL && fifo.i != 0)))
	{
		t = read_line(prompt, h, env, &g_sigint_line);
		if (t == NULL)
		{
			free(s);
			return (NULL);
		}
		getbraces(t, &fifo);
		s = addline(h, prompt, s, t);
	}
	if (g_sigint_line)
		s[0] = '\0';
	signal(SIGINT, SIG_IGN);
	return (s);
}
