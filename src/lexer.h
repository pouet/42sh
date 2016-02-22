/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 10:18:33 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/22 11:07:32 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define BUFF_SZ 2048

/*
** MUST BE IN LENGTH REVERSE ORDER
*/
# define X00 X( S_HERESTR,		"<<<", 3)
# define X01 X( S_HEREDOC,		"<<",  2)
# define X02 X( S_APPENDOUT,	">>",  2)
# define X03 X( S_DUPIN,		"<&",  2)
# define X04 X( S_DUPOUT,		">&",  2)
# define X05 X( S_REDIRINOUT,	"<>",  2)
# define X06 X( S_AND,			"&&",  2)
# define X07 X( S_OR,			"||",  2)
# define X08 X( S_SEMICOL,		";",   1)
# define X09
# define X10 X( S_PIPE,			"|",   1)
# define X11 X( S_REDIRIN,		"<",   1)
# define X12 X( S_REDIROUT,		">",   1)
# define X13 X( S_DQUOTE,		"\"",  1)
# define X14 X( S_SQUOTE,		"'",  1)
# define X15 X( S_BACKQUOTE,	"`",  1)
# define X16 X( S_LHOOK,		"[",  1)
# define X17 X( S_RHOOK,		"]",   1)
# define X18 X( S_LBRACE,		"{",   1)
# define X19 X( S_RBRACE,		"}",   1)
# define X20 X( S_LPAR,			"(",   1)
# define X21 X( S_RPAR,			")",   1)
# define X22 X( S_EQUAL,		"=",   1)
# define X23 //X( S_PLUS,			"+",   1)
# define X24 X( S_IDENT,		"",    0)
# define X25 X( S_NUMBER,		"",    0)
# define X26 X( S_BUILTIN,		"",    0)
# define X27 X( S_UNKNOWN,		"",    0)
# define X28 X( S_COMMAND,		"",    0)
# define XSEP X( S_SEPARATOR,	"",    0)
# define XEOL X( S_EOL,			"",    0)
# define XMAX X( S_MAX,			"",    0)

# define M0 X00 X01 X02 X03 X04 X05 X06 X07 X08 X09
# define M1 X10 X11 X12 X13 X14 X15 X16 X17 X18 X19
# define M2 X20 X21 X22 X23 X24 X25 X26 X27 X28

# define MACRO M0 M1 M2 XSEP XEOL XMAX

/*
** X(S_BACKSLASH, { "\\", 1 })\
** X(S_STAR, { "*", 1 })\
** X(S_INTERROGATION, { "?", 1 })\
** X(S_MINUS, { "-", 1 })
*/

# define X(e, s, len) e,

typedef enum		e_symbol
{
	MACRO
}					t_symbol;

# undef X

typedef struct		s_string
{
	char			*s;
	size_t			len;
}					t_string;

typedef struct		s_token
{
	t_symbol		sym;
	int				num;
	char			s[BUFF_SZ + 1];
	size_t			slen;
	unsigned		btin_num;
}					t_token;

extern t_string		g_symbol[S_MAX + 1];

t_token				*lexer(char *s);

#endif
