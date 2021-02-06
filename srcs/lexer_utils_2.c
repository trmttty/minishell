/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/06 12:50:33 by ttarumot         ###   ########.fr       */
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
		if ((lexer->c == '"' || lexer->c == '\''))
			return (lexer_collect_string(lexer));
		if (ft_strchr("<>|", lexer->c))
		{
			return (lexer_advance_with_token(lexer, init_token(TK_RESERVED, \
					lexer_get_current_char(lexer))));
		}
		if (lexer->c == ';')
		{
			lexer_advance(lexer);
			return (NULL);
		}
		return (lexer_collect_string(lexer));
	}
	return (NULL);
}

t_token		*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	char	*new_value;

	lexer_advance(lexer);
	if (token->kind == TK_RESERVED && !ft_strcmp(token->value, ">")
		&& lexer->c == '>')
	{
		if ((new_value = ft_strjoin(token->value, ">")) == NULL)
			ft_perror("minishell");
		free(token->value);
		token->value = new_value;
		lexer_advance(lexer);
	}
	return (token);
}

char		*lexer_get_current_char(t_lexer *lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
