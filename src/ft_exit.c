/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 16:06:02 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/16 09:10:19 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_exit.h"
#include "parser.h"
#include "ft_env.h"
#include "error.h"

int		ft_isnumber(char *s)
{
	while (*s && ft_isdigit(*s))
		s++;
	return (*s == '\0');
}

t_env	*ft_exit(t_env *env, t_tree *tree)
{
	int			i;
	unsigned	n;

	i = 1;
	while (i < tree->nchild && tree->child[i]->token->sym == S_SEPARATOR)
		i++;
	if (i >= tree->nchild)
		n = 0;
	else
	{
		n = 255;
		if (!ft_isnumber(tree->child[i]->token->s))
			eprintf("exit: %s: numeric argument required\n",
					tree->child[i++]->token->s);
		else
			n = ft_atoi(tree->child[i++]->token->s);
		if (n > 255)
			n = 0;
		while (i < tree->nchild && tree->child[i]->token->sym == S_SEPARATOR)
			i++;
		if (i < tree->nchild)
		{
			eprintf("exit: too many arguments\n");
			return (env);
		}
	}
	exit(n);
}
