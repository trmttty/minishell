/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/05 00:23:32 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

t_token		*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_skip_whitespace(lexer);
		if (lexer->c == ';')
		{
			lexer_advance(lexer);
			return (NULL);
		}
		if (lexer->pc == ' ' && (lexer->c == '"' || lexer->c == '\''))
			return (lexer_collect_string(lexer, lexer->c));
		if (ft_strchr("<>|", lexer->c))
		{
			return (lexer_advance_with_token(lexer, init_token(TK_RESERVED, \
					lexer_get_current_char_as_string(lexer))));
		}
		return (lexer_collect_string(lexer, 0));
	}
	return (NULL);
}

t_token		*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	char	*new_token;

	lexer_advance(lexer);
	if (token->kind == TK_RESERVED && !ft_strcmp(token->value, ">")
		&& lexer->c == '>')
	{
		new_token = ft_strjoin(token->value, ">");
		free(token->value);
		token->value = new_token;
		lexer_advance(lexer);
	}
	return (token);
}

char		*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
