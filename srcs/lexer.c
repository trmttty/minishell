/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/14 02:47:15 by ttarumot         ###   ########.fr       */
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
		if (lexer->c == '\0')
			break ;
		if ((lexer->c == '"' || lexer->c == '\'') && !lexer->env)
			return (lexer_collect_string(lexer));
		if (ft_strchr("<>|", lexer->c) && !lexer->env)
		{
			return (lexer_advance_with_token(lexer,
					init_token(TK_RESERVED, lexer_get_current_char(lexer))));
		}
		if (lexer->c == ';' && !lexer->env)
		{
			lexer_advance(lexer);
			return (NULL);
		}
		return (lexer_collect_string(lexer));
	}
	return (NULL);
}
