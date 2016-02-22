/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:06:27 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/22 14:46:43 by nchrupal         ###   ########.fr       */
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

void	putprompt(void)
{
	ft_putstr("$> ");
}

void	mainloop(void)
{
	char	s[BUFF_SZ + 1];
	int		ret;
	t_token	*token;
	t_tree	*tree;
	t_env	*env;

	env = create_env_environ();
	while (42)
	{
		putprompt();
		ret = read(0, s, BUFF_SZ);
		if (ret <= 0)
			break ;
		s[ret] = '\0';
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
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	mainloop();
	return (0);
}
