/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_restore.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:19:48 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 14:20:28 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAVE_RESTORE_H
# define SAVE_RESTORE_H

void	save_stdfd(int fd[3]);
void	restore_stdfd(int fd[3]);
void	restore_sigdfl(void);

#endif
