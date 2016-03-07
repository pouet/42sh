#include "libft.h"
#include "completion.h"
#include "print.h"
#include "ft_env.h"
#include "read_line.h"
#include "hashtable.h"

void	movecur_last(t_line *l)
{
	if (l->currow > 0)
		mv_cur("UP", 0, l->currow);
	ft_tputs("cr");
	if (l->row > 0)
		mv_cur("DO", 0, l->row);
	if (l->col > 0)
		mv_cur("RI", 0, l->col);
	ft_putendl("");
}

int		is_firstword(t_line *l, char *s)
{
	int		first;

	first = 0;
	s--;
	while (s > l->s && (*s == ' '))
	{
		s--;
	}
	if (s <= l->s || *s == ';' || *s == '|' || *s == '&')
		return (1);
	return (0);
}

int		cmd_count(t_hash *hash, char *s, int len)
{
	int		n;

	n = 0;
	while (hash && ft_strncmp(hash->cmd, s, len) == 0)
	{
		n++;
//		puts(hash->cmd);
		hash = hash->next;
	}
//	printf("%d\n", n);
	return (n);
}

int		add_completion(t_line *l, char *s, int len)
{
	while (s[len])
	{
		add_char(l, s[len]);
		len++;
	}
	return (1);
}

int		cmd_lenmax(t_hash *hash, int ncmd)
{
	int		lenmax;
	int		len;
	int		i;

	lenmax = 0;
	i = 0;
	while (hash && i < ncmd)
	{
		len = ft_strlen(hash->cmd);
		if (len > lenmax)
			lenmax = len;
		hash = hash->next;
		i++;
	}
	return (lenmax);
}

#include <unistd.h>
#include "ft_printf.h"

void	print_cmd(t_line *l, t_hash *hash, int ncmd, int lenmax)
{
	int		len;
	int		col;
	int		wid;
	int		i;
	int		j;

	col = l->wincol / (lenmax + 1);
	wid = l->wincol / col;
//	printf("%d - %d - %d - %d - %d\n", ncmd, lenmax, l->wincol, col, wid);
	j = 0;
	while (j < ncmd)
	{
		if (j != 0 && j % col == 0)
			ft_putchar('\n');
		len = ft_strlen(hash->cmd);
		ft_putstr(hash->cmd);
		i = len;
		while (i < wid)
		{
			ft_putchar(' ');
			i++;
		}
		hash = hash->next;
		j++;
	}
	ft_putchar('\n');
}

int		cmd_multiple(t_line *l, t_hash *hash, int ncmd)
{
//	int		lenmax;
	char	c;

	movecur_last(l);
	if (ncmd > 100)
	{
		ft_printf("Display all %d possibilities ? (y/n)", ncmd);
		while (read(0, &c, 1) > 0 && c != 'y' && c != 'n')
			;
		ft_putendl("");
		if (c == 'n')
			return (0);
	}
//	lenmax = cmd_lenmax(hash, ncmd);
	print_cmd(l, hash, ncmd, cmd_lenmax(hash, ncmd));

	return (1);
}

int		cmd_completion(t_line *l, t_env *env, char *s, int len)
{
	t_hash	*hash;
	int		ncmd;

	if (env == NULL)
		return (0);
	hash = env->content;
	hash = hash + SZHASH;
	hash = hash->next;
	while (hash != NULL)
	{
		ncmd = cmd_count(hash, s, len);
		if (ncmd == 1)
		{
			add_completion(l, hash->cmd, len);
			break ;
		}
		if (ncmd > 0)
		{
			cmd_multiple(l, hash, ncmd);
			return (1);
		}
		hash = hash->next;
	}
	return (0);
}

#include <dirent.h>
#include "expand.h"
#include "parser.h"
#include "lexer.h"

int		path_count(t_line *l, char *path, char *file, char *res)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				n;
	int				len;

	dirp = opendir(path);
	if (dirp == NULL)
		return (0);
	n = 0;
	len = ft_strlen(file);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (ft_strncmp(dp->d_name, file, len) == 0)
		{
			ft_strcpy(res, dp->d_name);
			n++;
		}
	}
	closedir(dirp);
	return (n);
}

int		path_complete(t_line *l, char *s, int len)
{
	while (s[len])
	{
		add_char(l, s[len]);
		len++;
	}
	return (0);
}

int		path_multiple(t_line *l, char *path, char *file)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				n;
	int				len;

	dirp = opendir(path);
	if (dirp == NULL)
		return (0);
	puts("");
	n = 0;
	len = ft_strlen(file);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (ft_strncmp(dp->d_name, file, len) == 0)
		{
			puts(dp->d_name);
		}
	}
	closedir(dirp);
	return (0);
}

int		path_completion(t_line *l, t_env *env, char *s, int len)
{
	t_tree	tree;
	t_token	token;
	char	*t;
	char	res[BUFF_SZ + 1];
	int		npath;

	tree.type = T_NAME;
	tree.token = &token;
	tree.token->sym = S_IDENT;
	ft_strncpy(token.s, s, len);
	token.s[len] = '\0';
	expand_tilde(&tree, env);
	if (token.s[0] != '/')
	{
		getcwd(token.s, BUFF_SZ);
		ft_strlcat(token.s, "/", BUFF_SZ);
		ft_strlcat(token.s, s, BUFF_SZ);
	}
	t = token.s + ft_strlen(token.s);
	while (t > token.s && *t != '/')
		t--;
	if (t == token.s && *t == '/')
	{
		ft_memmove(token.s + 1, token.s, ft_strlen(token.s) + 1);
		token.s[1] = '\0';
		t = token.s + 2;
	}
	else if (t != token.s && *t == '/')
		*t++ = '\0';
	npath = path_count(l, token.s, t, res);
	if (npath == 1)
		return (path_complete(l, res, ft_strlen(t)));
	else if (npath > 1)
		return (path_multiple(l, token.s, t));
	return (0);
}

int		completion(t_line *l, t_env *env)
{
	char	*s;
	int		len;

	s = l->s + l->i - 1;
	while (s > l->s && (ft_isalnum(*s) || *s == '~' || *s == '/'))
		s--;
	if (s != l->s)
		s++;
	len = (l->s + l->i) - s;
//	printf("%d - %s - %d\n", len, s, is_firstword(l, s));
	if (is_firstword(l, s))
		return (cmd_completion(l, env, s, len));
	else
		return (path_completion(l, env, s, len));
}
