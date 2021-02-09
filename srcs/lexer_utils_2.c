/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/07 12:12:30 by ttarumot         ###   ########.fr       */
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

static void	replace_environ_next(t_lexer *lexer, char **value,
									char *sub, size_t tail)
{
	size_t	len;

	if ((len = ft_strlen(sub)) > 0)
	{
		if ((*value = ft_realloc(*value,
			(ft_strlen(*value) + len + 1) * sizeof(char))) == NULL)
			ft_perror("minishell");
		ft_strlcat(*value, sub, ft_strlen(*value) + len + 1);
	}
	free(sub);
	while (tail--)
		lexer_advance(lexer);
}

void		replace_environ(t_lexer *lexer, char **value)
{
	char	*tmp;
	char	*sub;
	size_t	tail;

	tail = 1;
	while (ft_isalnum(lexer->contents[lexer->i + tail])
			|| lexer->contents[lexer->i + tail] == '_')
		tail++;
	if (lexer->contents[lexer->i + tail] == '?')
		tail++;
	if (tail == 1)
	{
		if ((sub = ft_substr(&lexer->contents[lexer->i], 0, tail)) == NULL)
			ft_perror("minishell");
	}
	else
	{
		if ((tmp = ft_substr(&lexer->contents[lexer->i], 0, tail)) == NULL)
			ft_perror("minishell");
		sub = get_env(&tmp[1]);
		free(tmp);
	}
	return (replace_environ_next(lexer, value, sub, tail));
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
