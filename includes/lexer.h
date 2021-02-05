/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 00:09:13 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/05 18:13:30 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "token.h"
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>

typedef struct		s_lexer
{
	char			pc;
	char			c;
	char			nc;
	char			quote;
	unsigned int	i;
	char*			contents;
}					t_lexer;

t_lexer		*new_lexer(char* contents);

void lexer_advance(t_lexer* lexer);

void lexer_skip_whitespace(t_lexer* lexer);

t_token* lexer_get_next_token(t_lexer* lexer);

t_token* lexer_collect_string(t_lexer* lexer, char quote);

t_token* lexer_collect_id(t_lexer* lexer);

t_token* lexer_advance_with_token(t_lexer* lexer, t_token* token);

char* lexer_get_current_char(t_lexer* lexer);

t_token		*generate_token(t_lexer *lexer);
int			is_escaped(char *s, int pos);
int			in_bracket(char *s, int pos);
char		*trim_value(char *value);
void		replace_environ(t_lexer* lexer, char **value);
t_token		*lexer_get_next_checker(t_lexer* lexer);
#endif
