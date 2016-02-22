/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 10:10:33 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/22 15:05:42 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define XE00  X( E_NOERROR,    "no error")
# define XE01  X( E_SYNTAX,     "syntax error near unexpexted token ")
# define XE02  X( E_MISSBRACE,  "missing close brace")
# define XE03  X( E_UNKCMD,     "command not found")
# define XE04  X( E_OPTION,     "unknown option -- ")
# define XE05  X( E_NOFORDIR,   "no such file or directory")
# define XE06  X( E_ISNODIR,    "not a directory")
# define XE07  X( E_BADFD,      "bad file descriptor")
# define XE08  X( E_PERMISSION, "permission denied")
# define XE09  X( E_NUMARG,     "numeric argument required")
# define XE10  X( E_TOOARGS,    "too many arguments")
# define XEUKN X( E_UNKNOWN,    "unknown error")
# define XEMAX X( E_MAX,        "")

# define EM00 XE00 XE01 XE02 XE03 XE04 XE05 XE06 XE07 XE08 XE09
# define EM10 XE10
# define EMACRO EM00 EM10 XEUKN XEMAX

# define X(e, s) e,

typedef enum
{
	EMACRO
}	t_error;

# undef X

extern char	*g_error[E_MAX + 1];
extern int	g_errno;

int		eprintf(char *fmt, ...);

#endif
