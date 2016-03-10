/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:20:47 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/10 15:15:58 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "ft_cd.h"

int		del_multipleslash(char *s, int len)
{
	char	*t;
	char	*sav;

	sav = s;
	while (*s)
	{
		if (*s == '/' && *(s + 1) == '/')
		{
			t = s + 1;
			while (*t == '/')
				t++;
			ft_strcpy(s + 1, t);
			len -= t - (s + 1);
		}
		s++;
	}
	sav[len] = '\0';
	return (len);
}

int		del_finalslash(char *s, int len)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	if (i > 1 && s[i - 1] == '/')
	{
		s[i - 1] = '\0';
		len--;
	}
	return (len);
}

int		del_dotslash(char *s, int len)
{
	char	name[BUFF_SZ + 1];
	char	*t;
	int		i;

	i = 0;
	while (i < len && s[i])
	{
		len = del_multipleslash(s, len);
		len = del_finalslash(s, len);
		t = get_nextid(s + i, name);
		if (ft_strcmp(name, ".") == 0 && i > 0)
		{
			ft_strcpy(s + i, t);
			len--;
			s[len] = '\0';
		}
		else
		{
			i += t - (s + i);
		}
	}
	s[len] = '\0';
	return (len);
}

int		del_dotdot(char *s, int len)
{
	char	name[BUFF_SZ + 1];
	char	*t;
	int		i;

	i = 0;
	while (i < len && s[i])
	{
		len = del_multipleslash(s, len);
		len = del_finalslash(s, len);
		t = get_nextid(s + i, name);
		if (ft_strcmp(name, "..") == 0)
		{
			s = move_dotdot(s, t, &len, i);
			i = 0;
		}
		else
			i += t - (s + i);
	}
	return (len);
}
