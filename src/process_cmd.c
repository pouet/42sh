/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 12:12:11 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 15:01:20 by nchrupal         ###   ########.fr       */
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
#include "hashtable.h"
#include "save_restore.h"
#include "pipe_cmd.h"
#include "search_cmd.h"

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
	"",
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

t_builtinlist g_bt[NBUILTIN] = {
	{ "env", ft_env },
	{ "cd", ft_cd },
	{ "exit", ft_exit },
	{ "setenv", ft_setenv },
	{ "unsetenv", ft_unsetenv }
};

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

int		checkstatus(int stat_loc)
{
	int		sig;

	if (WIFEXITED(stat_loc))
		return (WEXITSTATUS(stat_loc));
	if (WIFSIGNALED(stat_loc) && WCOREDUMP(stat_loc))
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
