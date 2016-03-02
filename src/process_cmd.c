/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 12:12:11 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/02 11:27:23 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include "libft.h"
#include "ft_printf.h"
#include "process_cmd.h"
#include "initterms.h"
#include "lexer.h"
#include "parser.h"
#include "ft_env.h"
#include "ft_setenv.h"
#include "error.h"
#include "ft_cd.h"
#include "ft_exit.h"
#include "redirections.h"

t_builtinlist g_bt[NBUILTIN] = {
	{ "env", ft_env },
	{ "cd", ft_cd },
	{ "exit", ft_exit },
	{ "setenv", ft_setenv },
	{ "unsetenv", ft_unsetenv }
};

int		is_builtin(char *s)
{
	int		i;

	i = 0;
	while (i < NBUILTIN)
	{
		if (ft_strcmp(g_bt[i].name, s) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*create_path(char *file, char *path, char *s)
{
	int		len;
	char	*p;

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
	return (p);
}

int		have_permission(char *cmd)
{
	struct stat	buf;
	uid_t		uid;
	gid_t		gid;

	uid = getuid();
	gid = getgid();
	if (stat(cmd, &buf) < 0)
		return (-1);
	if ((buf.st_uid == uid && (buf.st_mode & S_IXUSR)) ||
		(buf.st_gid == gid && (buf.st_mode & S_IXGRP)) ||
		(buf.st_mode & S_IXOTH))
		return (1);
	g_errno = E_PERMISSION;
	eprintf("%s: %s\n", cmd, g_error[g_errno]);
	return (0);
}

int		is_pathsearch(char *s, t_env *env)
{
	t_env	*env_path;
	char	*path;
	char	*p;
	char	file[BUFF_SZ + 1];

	path = "./";
	env_path = env_getname(env, "PATH");
	if (env_path != NULL)
		path = env_path->content + 5;
	while (*path)
	{
		p = create_path(file, path, s);
		if (have_permission(file) == 0)
			return (0);
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
	int		ret;

	if (token == NULL || ft_strcmp(token->s, ".") == 0
		|| ft_strcmp(token->s, "..") == 0)
		return (0);
	if (ft_strchr(token->s, '/'))
	{
		if (have_permission(token->s) == 0 || access(token->s, X_OK) != 0)
			return (0);
		token->sym = S_COMMAND;
	}
	else
	{
		if ((ret = is_builtin(token->s)) >= 0)
		{
			token->sym = S_BUILTIN;
			token->btin_num = ret;
		}
		else if (is_pathsearch(token->s, env))
			token->sym = S_COMMAND;
		else
			return (0);
	}
	return (1);
}

void	save_stdfd(int fd[3])
{
	fd[0] = dup(0);
	fd[1] = dup(1);
	fd[2] = dup(2);
}

void	restore_stdfd(int fd[3])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	dup2(fd[2], 2);
}

void	restore_sigdfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

int		launch_process(t_tree *tree, t_env *env)
{
	char		**av;
	char		**environ;

	av = tree_totab(tree);
	environ = env_totab(env);
	restore_sigdfl();
	execve(av[0], av, environ);
	eprintf("error: cannot launch '%s'\n", av[0]);
	exit(1);
}

#define N_SIG 32
static char		*g_ssig[N_SIG] = {
	"",
	"",
	"",
	"",
	"SIGILL: illegal instruction\n",
	"SIGTRAP: trace trap\n",
	"SIGABRT: abort program\n",
	"SIGEMT: emulate instruction executed\n",
	"SIGFPE: floating-point exception\n",
	"",
	"SIGBUS: bus error\n",
	"SIGSEGV: segmentation fault\n",
	"SIGSYS: non-existent system call invoked\n",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
};

int		checkstatus(int stat_loc)
{
	int		sig;

	if (WIFEXITED(stat_loc))
		return (WEXITSTATUS(stat_loc));
	if (WIFSIGNALED(stat_loc))
	{
		sig = WTERMSIG(stat_loc);
		if (sig > 0 && sig < N_SIG)
			eprintf("%s", g_ssig[sig]);
		return (sig);
	}
	return (0);
}

int		fork_process(t_tree *tree, t_env *env, t_env *new)
{
	pid_t	pid;
	int		fd_sav[3];
	int		stat_loc;

	save_stdfd(fd_sav);
	oper_redirection(tree);
	if (tree->child[0]->token->sym == S_BUILTIN)
		g_bt[tree->child[0]->token->btin_num].f(env, tree);
	else
	{
		pid = fork();
		if (pid < 0)
			eprintf("error: fork failed\n");
		else if (pid == 0)
			launch_process(tree, new);
		else
		{
			while (waitpid(pid, &stat_loc, WNOHANG) == 0)
				;
			checkstatus(stat_loc);
		}
	}
	restore_stdfd(fd_sav);
	return (0);
}

void	child_pipe(t_tree *tree, t_env *env, t_env *new, int fd_pipe[2])
{
	close(fd_pipe[0]);
	dup2(fd_pipe[1], 1);
	close(fd_pipe[1]);
	process_cmd(tree->child[0], env, new);
	exit(0);
}

int		do_pipe(t_tree *tree, t_env *env, t_env *new)
{
	int		fd_pipe[2];
	int		stat_loc;
	int		fd_sav;
	pid_t	pid;

	if (pipe(fd_pipe) < 0)
		return (eprintf("error: cannot create pipe\n"));
	if ((pid = fork()) < 0)
		return (eprintf("error: fork failed\n"));
	else if (pid == 0)
		child_pipe(tree, env, new, fd_pipe);
	else
	{
		fd_sav = dup(0);
		close(fd_pipe[1]);
		dup2(fd_pipe[0], 0);
		close(fd_pipe[0]);
		process_cmd(tree->child[1], env, new);
		dup2(fd_sav, 0);
		while (waitpid(pid, &stat_loc, WNOHANG) == 0)
			;
	}
	return (0);
}

int		process_cmd(t_tree *tree, t_env *env, t_env *new)
{
	if (tree)
	{
		if (tree->type == T_CMD)
		{
			if (find_cmd(tree->child[0]->token, env) != 0)
				fork_process(tree, env, new);
			else if (g_errno == E_NOERROR)
				eprintf("42sh: %s: %s\n", tree->child[0]->token->s,
						g_error[E_UNKCMD]);
		}
		else if (tree->type == T_SEMICOL)
		{
			process_cmd(tree->child[0], env, new);
			process_cmd(tree->child[1], env, new);
		}
		else if (tree->type == T_PIPE)
			do_pipe(tree, env, new);
		else if (g_errno == E_NOERROR)
			eprintf("42sh: %s: %s\n", tree->child[0]->token->s,
					g_error[E_UNKCMD]);
	}
	return (0);
}
