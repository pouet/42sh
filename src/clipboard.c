/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 10:32:22 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/25 11:46:03 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "read_line.h"
#include "clipboard.h"

static char	*g_clip;

void	clip_cut(enum e_clipboard type, t_line *l)
{
	if (l->len == 0)
		return ;
	if (type == C_CUTALL)
	{
		clip_copy(C_CPYALL, l);
		l->i = 0;
		l->len = 0;
		l->s[0] = '\0';
	}
	else if (type == C_CUTBEG && l->i > 0)
	{
		clip_copy(C_CPYBEG, l);
		ft_strcpy(l->s, l->s + l->i);
		l->i = 0;
		l->len = ft_strlen(l->s);
	}
	else if (type == C_CUTEND && l->i < l->len)
	{
		clip_copy(C_CPYEND, l);
		l->s[l->i] = '\0';
		l->len = l->i;
	}
}

void	clip_copy(enum e_clipboard type, t_line *l)
{
	if (l->len == 0)
		return ;
	if (type == C_CPYALL)
	{
		if (g_clip)
			free(g_clip);
		g_clip = ft_strdup(l->s);
	}
	else if (type == C_CPYBEG && l->i > 0)
	{
		if (g_clip)
			free(g_clip);
		g_clip = ft_strdup(l->s);
		g_clip[l->i] = '\0';
	}
	else if (type == C_CPYEND && l->i < l->len)
	{
		if (g_clip)
			free(g_clip);
		g_clip = ft_strdup(l->s + l->i);
	}
}

void	clip_paste(t_line *l)
{
	int		len;

	if (g_clip == NULL)
		return ;
	len = ft_strlen(g_clip);
	if (l->len + len >= l->lenmax)
		growup_line(l);
	ft_memmove(l->s + l->i + len, l->s + l->i, l->len - l->i + 1);
	ft_memcpy(l->s + l->i, g_clip, len);
	l->len = ft_strlen(l->s);
	l->i += len;
}
