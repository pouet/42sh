/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 12:12:11 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/17 14:12:07 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "process_cmd.h"
#include "lexer.h"
#include "parser.h"
#include "ft_env.h"
#include "ft_setenv.h"
#include "error.h"
#include "ft_cd.h"
#include "ft_exit.h"
#include "redirections.h"

t_builtinlist bt[NBUILTIN] = {
	{ "env" , ft_env },
	{ "cd" , ft_cd },
	{ "exit" , ft_exit },
	{ "setenv" , ft_setenv },
	{ "unsetenv", ft_unsetenv }
};

int		is_builtin(char *s)
{
	int		i;

	i = 0;
	while (i < NBUILTIN)
	{
		if (ft_strcmp(bt[i].name, s) == 0)
			return (1);
		i++;
	}
	return (0);
}

int		is_pathsearch(char *s, t_env *env)
{
	t_env	*env_path;
	char	*path;
	char	*p;
	int		len;
	char	file[BUFF_SZ + 1];

	path = "./";
	env_path = env_getname(env, "PATH");
	if (env_path != NULL)
		path = env_path->content + 5;
	while (*path)
	{
		len = BUFF_SZ;
		p = ft_strchr(path, ':');
		if (p != NULL)
			len = p - path;
		ft_strncpy(file, path, len);
		file[len] = '\0';
		if (len == 0)
			ft_strcpy(file, ".");
		ft_strlcat(file, "/", BUFF_SZ);
		ft_strlcat(file, s, BUFF_SZ);
		if (access(file, X_OK) == 0)
		{
			ft_strcpy(s, file);
			return (1);
		}
		if (p == NULL)
			break ;
		path = p + 1;
	}
	return (0);
}

int		find_cmd(t_token *token, t_env *env)
{
	if (token == NULL)
		return (0);
	if (ft_strchr(token->s, '/'))
	{
		if (access(token->s, X_OK) != 0)
			return (0);
		token->sym = S_COMMAND;
		/* TODO: lancer la commande direct. Pas de builtin ni de PATH search */
	}
	else
	{
		if (is_builtin(token->s))
			token->sym = S_BUILTIN;
		else if (is_pathsearch(token->s, env))
			token->sym = S_COMMAND;
		else
			return (0);
		/* TODO: lancer built-in/PATH search */
	}
	return (1);
}

#include <sys/wait.h>
#include <unistd.h>
int		fork_process(t_tree *tree, t_env *env, t_env *new)
{
	pid_t	pid;
	int		i;

	int fd0, fd1, fd2;

	fd0 = dup(0);
	fd1 = dup(1);
	fd2 = dup(2);

	oper_redirection(tree);

/*	dup2(tree->fd[0], 0);
	dup2(tree->fd[1], 1);
	dup2(tree->fd[2], 2);*/
	if (tree->child[0]->token->sym == S_BUILTIN)
	{
		i = 0;
		while (ft_strcmp(bt[i].name, tree->child[0]->token->s) != 0)
			i++;
		bt[i].f(env, tree);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			eprintf("error: fork failed\n");
		else if (pid == 0)
			//		if (tree->child[0]->token->sym == S_COMMAND)
		{
			char **av = tree_totab(tree);
			char **environ = env_totab(new);
			if (execve(av[0], av, environ) < 0)
				eprintf("error: cannot create processus\n");
		}
		else
		{
			int stat_loc;
			while (waitpid(pid, &stat_loc, WNOHANG) == 0)
				;
		}
	}
//	close(0);
//	close(1);
//	close(2);
//	close(tree->fd[0]);
//	close(tree->fd[1]);
//	close(tree->fd[2]);
	dup2(fd0, 0);
	dup2(fd1, 1);
	dup2(fd2, 2);
	return (0);
}
#include <stdio.h>
int		do_pipe(t_tree *tree, t_env *env, t_env *new)
{
	int		fd_pipe[2];
	int		stat_loc;
	int		fd_sav;
	pid_t	pid;

	if (pipe(fd_pipe) < 0)
		return (eprintf("error: cannot create pipe\n"));
//	tree->child[0]->fd[1] = fd_pipe[1];
//	tree->child[1]->fd[0] = fd_pipe[0];
	pid = fork();
	if (pid < 0)
		eprintf("error: fork failed\n");
	else if (pid == 0)
	{
		fd_sav = dup(0);

		close(fd_pipe[1]);
		dup2(fd_pipe[0], 0);

		fputs("PROUT\n", stderr);
		process_cmd(tree->child[1], env, new);
		close(fd_pipe[0]);
		dup2(fd_sav, 0);
		exit(0);
	}
	else
	{
		fd_sav = dup(1);

		close(fd_pipe[0]);
		dup2(fd_pipe[1], 1);

		fputs("prout\n", stderr);
		process_cmd(tree->child[0], env, new);

		close(fd_pipe[1]);
		dup2(fd_sav, 1);

		while (waitpid(pid, &stat_loc, WNOHANG) == 0)
			;
	}
	return (0);
}
#include <stdio.h>
#include "ft_printf.h"
int		process_cmd(t_tree *tree, t_env *env, t_env *new)
{
	if (tree)
	{
		if (tree->type == T_CMD)
		{
			/* TODO: lancer la commande avec les arguments */
			if (find_cmd(tree->child[0]->token, env) != 0)
				fork_process(tree, env, new);
			else
				eprintf("42sh: %s: %s\n", tree->child[0]->token->s,
						g_error[E_UNKCMD]);
		}
		else if (tree->type == T_SEMICOL)
		{
			process_cmd(tree->child[0], env, new);
			process_cmd(tree->child[1], env, new);
		}
		else if (tree->type == T_PIPE)
		{
			do_pipe(tree, env, new);
//			if (do_pipe(tree->child[0], tree->child[1]) >= 0)
//			{
/*				process_cmd(tree->child[0], env, new);
//				ft_printf_fd(tree->child[0]->fd[1], "%c", EOF);
//				close(tree->child[1]->fd[1]);
//				close(tree->child[0]->fd_pipetoclose);
				close(tree->child[0]->fd_pipetoclose[1]);
				process_cmd(tree->child[1], env, new);
//				ft_printf_fd(tree->child[1]->fd[0], "%c", EOF);
//				printf("%c", EOF);
//				close(tree->child[0]->fd_pipetoclose[0]);
				close(tree->child[1]->fd_pipetoclose[1]);
//				close(tree->child[1]->fd_pipetoclose);*/
//			}
		}
		else
			eprintf("42sh: %s: %s\n", tree->child[0]->token->s,
					g_error[E_UNKCMD]);
	}
	return (0);
}
