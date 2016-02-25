/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:06:27 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/25 16:37:17 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "ft_env.h"
#include "ft_setenv.h"
#include "expand.h"
#include "error.h"
#include "process_cmd.h"
#include "redirections.h"
#include "initterms.h"
#include "read_line.h"
#include "history.h"

typedef struct	s_fifo
{
	char		t[BUFF_SZ + 1];
	int			i;
}				t_fifo;

const char *g_corr = "\"\"''``[](){}";

int		fifo_push(t_fifo *fifo, char c)
{
	char		*t;

	t = ft_strchr(g_corr, c);
	if (t == NULL)
		return (0);
	if (fifo->i + 1 >= BUFF_SZ)
	{
		eprintf("error: too many braces\n");
		return (0);
	}
	fifo->t[fifo->i++] = *(t + 1);
	return (1);
}

char	fifo_pop(t_fifo *fifo)
{
	if (fifo->i - 1 < 0)
		return ('\0');
	fifo->i--;
	return (fifo->t[fifo->i]);
}

void	getbraces(char *s, t_fifo *fifo)
{
	char	*t;
	int		index;

	while (s && *s)
	{
		t = ft_strchr(g_corr, *s);
		if (t != NULL)
		{
			index = t - g_corr;
			printf("%d", index);
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

char	*getline(t_history *h)
{
	t_fifo	fifo;
	char	*s;
	char	*t;

	ft_bzero(&fifo, sizeof(fifo));
	s = read_line(h);
	getbraces(s, &fifo);
	puts("");
	for (int i = 0; i < fifo.i; i++)
		printf("[%c]", fifo.t[i]);
	puts("");
	return (s);
}

void	putprompt(void)
{
	ft_putstr("$> ");
}

void	mainloop(void)
{
//	char	s[BUFF_SZ + 1];
//	int		ret;
	t_history	h;
	t_token		*token;
	t_tree		*tree;
	t_env		*env;
	char		*s;

	env = create_env_environ();
	histo_load(&h);
	while (42)
	{
		putprompt();
//		s = read_line(&h);
		s = getline(&h);
		if (s == NULL)
			break ;
//		ret = read(0, s, BUFF_SZ);
//		if (ret <= 0)
//			break ;
//		s[ret] = '\0';
		token = lexer(s);
		if (token != NULL)
		{
			tree = parser(token);
			if (tree != NULL)
			{
				expand_all(tree, env);
				process_cmd(tree, env, env);
			}
		}
	}
}

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	if (init_term() < 0)
		return (1);
	set_terms();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	mainloop();
	unset_terms();
	return (0);
}
