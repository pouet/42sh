/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:06:27 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/23 10:37:55 by nchrupal         ###   ########.fr       */
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

void	putprompt(void)
{
	ft_putstr("$> ");
}

void	mainloop(void)
{
//	char	s[BUFF_SZ + 1];
	int		ret;
	t_token	*token;
	t_tree	*tree;
	t_env	*env;
	char	*s;

	env = create_env_environ();
	while (42)
	{
		putprompt();
		s = read_line(42);
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
	struct termios	new;
	struct termios	old;

	(void)ac;
	(void)av;
	if (init_term() < 0)
		return (1);
	set_terms(&old, &new);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	mainloop();
	unset_terms(&old);
	return (0);
}
