/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/15 13:06:36 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

t_token		*lexer_get_next_checker(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_skip_whitespace(lexer);
		if (lexer->pc == ' ' && (lexer->c == '"' || lexer->c == '\''))
			return (lexer_collect_string(lexer));
		if (ft_strchr(";<>|", lexer->c))
		{
			return (lexer_advance_with_token(lexer, init_token(TK_RESERVED,
					lexer_get_current_char(lexer))));
		}
		return (lexer_collect_string(lexer));
	}
	return (NULL);
}

int			ft_isquote(char c)
{
	return (c == '"' || c == '\'');
}

int			in_bracket(t_lexer *lexer)
{
	if (lexer->quote == '\0' && ft_isquote(lexer->c))
	{
		lexer->quote = lexer->c;
		return (1);
	}
	if (ft_isquote(lexer->quote) && lexer->quote == lexer->c)
	{
		lexer->quote = '\0';
		return (0);
	}
	return (ft_isquote(lexer->quote));
}

void		free_lexer(t_lexer *lexer)
{
	free(lexer->contents);
	free(lexer);
}
