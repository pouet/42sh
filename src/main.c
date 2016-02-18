/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:06:27 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/18 15:28:07 by nchrupal         ###   ########.fr       */
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

void	print_tree(t_tree *tree)
{
	if (tree)
	{
		if (tree->type == T_CMD)
		{
//			printf("CMD: %d child ", tree->nchild);
			for (int i = 0; i < tree->nchild; i++) {
//				if (tree->type == T_BRACE)
					print_tree(tree->child[i]);
//				else if (tree->child[i]->token)
//					printf("[%s] ", tree->child[i]->token->s);
//				else
//					puts("probleme...");
			}
			puts("");
		}
		else if (tree->type == T_BRACE || tree->type == T_SEMICOL || tree->type == T_PIPE)
		{
			print_tree(tree->child[0]);
			if (tree->type == T_SEMICOL)
				puts("SEMICOL:");
			if (tree->type == T_BRACE)
				puts("PAR:");
			if (tree->type == T_PIPE)
				puts("PIPE:");
			printf("\t");
			print_tree(tree->child[1]);
		}
		else if (tree->nchild == 0)
			if (tree->token)
			{
				if (tree->token->sym == S_SEPARATOR)
					printf("[] ");
				else
					printf("[%s] ", tree->token->s);
			}
			else
				puts("probleme...");
		else
			puts("probleme...");
	}
}

void	mainloop(void)
{
	char	s[BUFF_SZ + 1];
	int		ret;
	t_token	*token;
	t_tree	*tree;
	t_env	*env;

	env = create_env_environ();
/*	{
		char **av = env_totab(env);
		for (int i = 0; av[i]; i++)
			puts(av[i]);
	}*/
//	ft_env(env);
//	if (env_getname(env, "PATH"))
//		puts(env_getname(env, "PATH")->content);
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
			for (int i = 0; token[i].sym != S_EOL; i++) {
				printf("%2d: ", token[i].sym);
				puts(token[i].s);
			}
			puts("/-----/");
			tree = parser(token);
			if (tree != NULL)
			{
				print_tree(tree);
				puts("/--------/");
				expand_all(tree, env);
				print_tree(tree);
//				puts("/--------/");
//				print_tree(tree);
				process_cmd(tree, env, env);
			}
			else
				puts("(TREE NULL)");
		}
	}
}

#include <unistd.h>
int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	signal (SIGINT, SIG_IGN);
	signal (SIGQUIT, SIG_IGN);
	signal (SIGTSTP, SIG_IGN);
	signal (SIGTTIN, SIG_IGN);
	signal (SIGTTOU, SIG_IGN);
	signal (SIGCHLD, SIG_IGN);
	mainloop();
	return (0);
}
