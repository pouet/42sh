/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 12:25:46 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 14:13:24 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "parser.h"

int		oper_redirection(t_tree *tree);
int		get_nbr(char *s, char **t);
void	del_redir(t_tree *tree, int start, int end);
int		do_redirection(t_tree *tree, int i);
int		cmd_redirection(t_tree *tree);
int		heredoc(t_symbol sym, char *redir, char *word);
char	*join_heredoc(char *s, char *t);
int		dup_fd(t_symbol sym, char *redir, char *word);
int		redir(t_symbol sym, char *redir, char *word);

#endif
