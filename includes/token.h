/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 00:09:27 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/07 14:45:56 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include <ctype.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef enum		e_token_kind
{
	TK_RESERVED,
	TK_CMD,
	TK_SKIP,
	TK_SEMI,
	TK_EOF,
}					t_token_kind;

typedef struct		s_token
{
	t_token_kind	kind;
	char			*value;
	struct s_token	*next;
}					t_token;

t_token				*g_token;

t_token				*init_token(t_token_kind type, char *value);
bool				consume(char *op);
void				expect(char op);
char				**expect_command(void);
bool				at_eof(void);
t_token				*new_token(t_token_kind kind, t_token *cur, char *op);
t_token				*parse_token(t_token *token);
void				free_token(t_token *token);
void				sort_token(void);
int					check_syntax(char *line);

#endif
