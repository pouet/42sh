/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:06:27 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/02 10:00:55 by nchrupal         ###   ########.fr       */
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
#include "xmalloc.h"
#include <time.h>
#include "colors.h"

void	getprompt(char *s, unsigned len)
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
			if (fifo->i > 0 && index < 6 && *s == fifo->t[fifo->i - 1])
				index++;
//			printf("%d", index);
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

char	*getline(t_history *h, t_env *env)
{
	char	prompt[BUFF_SZ + 1];
	t_fifo	fifo;
	char	*s;
	char	*t;
	char	*tmp;

	s = NULL;
	ft_bzero(&fifo, sizeof(fifo));
	getprompt(prompt, BUFF_SZ);
	while (s == NULL || (s != NULL && fifo.i != 0))
	{
		t = read_line(prompt, h, env);
		if (t == NULL)
		{
			free(s);
			return (NULL);
		}
		getbraces(t, &fifo);
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
//		printf("[%s][%d]\n", s, fifo.i);
	}
	return (s);
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
//		s = read_line(&h);
		s = getline(&h, env);
		if (s == NULL)
			break ;
//		printf("[%s]\n", s);
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
				unset_terms();
				process_cmd(tree, env, env);
				set_terms();
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
