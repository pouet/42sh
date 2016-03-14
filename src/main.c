/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:06:27 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/14 09:25:35 by nchrupal         ###   ########.fr       */
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
#include "getline.h"

void	mainloop(void)
{
	t_history	h;
	t_token		*token;
	t_tree		*tree;
	t_env		*env;
	char		*s;

	env = create_env_environ();
	histo_load(&h);
	while (42)
	{
		s = getline(&h, env);
		if (s == NULL)
			break ;
		token = lexer(s);
		if (token != NULL && (tree = parser(token)) != NULL)
		{
			expand_all(tree, env);
			unset_terms();
			process_cmd(tree, env, env);
			set_terms();
		}
	}
	free(env);
	histo_del(&h);
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
