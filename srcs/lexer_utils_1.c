/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/10 16:05:24 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

t_lexer		*new_lexer(char *contents)
{
	t_lexer	*lexer;

	if ((lexer = ft_calloc(1, sizeof(t_lexer))) == NULL)
		ft_perror("minishell");
	if ((lexer->contents = ft_strdup(contents)) == NULL)
		ft_perror("minishell");
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	lexer->nc = contents[lexer->i + 1];
	if (ft_isquote(lexer->c))
		lexer->quote = lexer->c;
	return (lexer);
}

void		lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->pc = lexer->contents[lexer->i];
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
		lexer->nc = lexer->contents[lexer->i + 1];
		if (lexer->env > 0)
			lexer->env -= 1;
	}
	if (lexer->env == 0 && lexer->escape == 0)
		in_bracket(lexer);
}

void		lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t')
	{
		lexer_advance(lexer);
	}
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
