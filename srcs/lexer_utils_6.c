/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/15 13:10:12 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

int			lexer_escape_string_raw(t_lexer *lexer, char **value)
{
	char	*str;
	size_t	size;

	lexer->escape = 1;
	if (lexer->quote == 0 && lexer->nc == '\n')
	{
		lexer_collect_current_char(lexer, value);
		lexer_collect_current_char(lexer, value);
	}
	else if (lexer->quote == 0)
		lexer_collect_current_char(lexer, value);
	else if (lexer->quote == '"' && ft_strchr("$`\"\\\n", lexer->nc))
		lexer_collect_current_char(lexer, value);
	lexer->escape = 0;
	str = lexer_get_current_char(lexer);
	size = ft_strlen(*value) + ft_strlen(str) + 1;
	if ((*value = ft_realloc(*value, size * sizeof(char))) == NULL)
		ft_perror("minishell");
	ft_strlcat(*value, str, size);
	free(str);
	lexer_advance(lexer);
	return (0);
}

int			lexer_skip_quote_raw(t_lexer *lexer)
{
	if (lexer->quote && lexer->quote == lexer->c && !lexer->env)
		return (1);
	else if (!lexer->quote && ft_isquote(lexer->c)
			&& !lexer->env)
		return (1);
	return (0);
}

t_token		*lexer_loop_raw(t_lexer *lexer, char **value)
{
	while (lexer->c != '\0')
	{
		if (lexer_skip_quote_raw(lexer))
			lexer_collect_current_char(lexer, value);
		else if (lexer_return_string(lexer))
			break ;
		else if (ft_isescape(lexer) && !lexer->env)
		{
			if (lexer_escape_string_raw(lexer, value))
				break ;
		}
		else
			lexer_collect_current_char(lexer, value);
	}
	return (NULL);
}
