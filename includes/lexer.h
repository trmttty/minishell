/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 00:09:13 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/15 18:30:22 by ttarumot         ###   ########.fr       */
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
	size_t			env;
	int				escape;
	int				raw;
	char			*contents;
}					t_lexer;

t_lexer				*new_lexer(char *contents, int raw);
void				lexer_advance(t_lexer *lexer);
void				lexer_skip_whitespace(t_lexer *lexer);
void				lexer_collect_current_char(t_lexer *lexer, char **value);
t_token				*lexer_get_next_token(t_lexer *lexer);
t_token				*lexer_collect_string(t_lexer *lexer);
t_token				*lexer_collect_id(t_lexer *lexer);
t_token				*lexer_advance_with_token(t_lexer *lexer, t_token *token);
t_token				*generate_token(t_lexer *lexer);
t_token				*lexer_get_next_checker(t_lexer *lexer);
int					lexer_return_string(t_lexer *lexer);
char				*lexer_get_current_char(t_lexer *lexer);
int					is_escaped(char *s, int pos);
int					in_bracket(t_lexer *lexer);
int					ft_isquote(char c);
char				*trim_value(char *value);
int					lexer_skip_quote(t_lexer *lexer);
int					lexer_escape_string(t_lexer *lexer, char **value);
int					ft_isescape(t_lexer *lexer);
int					lexer_expand_env(t_lexer *lexer, char **value);
void				update_contens(t_lexer *lexer, char *ret, char **value);
char				*lexer_get_exit_code(t_lexer *lexer);
t_token				*lexer_loop_raw(t_lexer *lexer, char **value);
char				**lexer_expand_command(char **commands);
char				**lexer_expand_file_name(char **commands);
void				free_lexer(t_lexer *lexer);

#endif
