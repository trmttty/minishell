/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 00:09:27 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/20 00:09:29 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
#define TOKEN_H

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Tokenizer
//

typedef enum		u_token_kind{
	TK_RESERVED, // Keywords or punctuators
	TK_CMD,      // Integer literals
	TK_EOF,      // End-of-file markers
}					t_token_kind;

// Token type
typedef struct		s_token
{
	t_token_kind	kind;
	char			*value;		// Token value 
	struct s_token	*next;		// Next token
}					t_token;

// Current token
t_token		*g_token;

t_token*	init_token(t_token_kind type, char* value);

void error(char *fmt, ...);

// Reports an error location and exit.
void error_at(char *loc, char *fmt, ...);

// Consumes the current token if it matches `op`.
bool consume(char op);

// Ensure that the current token is `op`.
void expect(char op);

// Ensure that the current token is TK_NUM.
char **expect_command();

bool at_eof();

// Create a new token and add it as the next token of `cur`.
t_token *new_token(t_token_kind kind, t_token *cur, char *op);

t_token		*tokenize(char *job);

#endif
