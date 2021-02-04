/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/04 16:22:59 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

t_token*    lexer_collect_string(t_lexer* lexer, char quote)
{
	char    *value;
	char    *s;
	size_t  size;

	if ((value = ft_calloc(1, sizeof(char))) == NULL)
		ft_perror("minishell");
	value[0] = '\0';
	while (lexer->c != '\0')
	{
		// fprintf(stderr, "lexer: [%c] [%c] [%c] [%d] [%s]\n", lexer->pc, lexer->c, lexer->nc, in_bracket(lexer->contents, lexer->i), value);
		if (lexer->c == '\\')
		{
			lexer_advance(lexer);
			s = lexer_get_current_char_as_string(lexer);
			size = ft_strlen(value) + ft_strlen(s) + 1;
			if ((value = ft_realloc(value, size * sizeof(char))) == NULL)
				ft_perror("minishell");
			ft_strlcat(value, s, size);
			free(s);
			if (!in_bracket(lexer->contents, lexer->i) && ft_strchr(";|<>", lexer->nc))
			{
				break;
			}
			lexer_advance(lexer);
			continue;
		}
		if (!in_bracket(lexer->contents, lexer->i) && ft_strchr(";|<>", lexer->c))
		{
			break;
		}
		if (in_bracket(lexer->contents, lexer->i) && lexer->c == quote)
		{
			lexer_advance(lexer);
			continue;
		}	
		if (!in_bracket(lexer->contents, lexer->i) && lexer->c == quote && !(lexer->nc == ' ' || lexer->nc == '\0'))
		{
			lexer_advance(lexer);
			continue;
		}

		if (lexer->i && !in_bracket(lexer->contents, lexer->i - 1) && in_bracket(lexer->contents, lexer->i) && lexer->c != quote && (lexer->c == '"' || lexer->c == '\''))
		{
			quote = lexer->c;
			continue;
		}
		if (!in_bracket(lexer->contents, lexer->i) && lexer->c == quote)
		{
			break;
		}
		if (!in_bracket(lexer->contents, lexer->i) && lexer->c == ' ')
		{
			break;
		}
		if (lexer->c == '$' && quote != '\'')
		{
			while (lexer->c == '$' && quote != '\'')
			{
				replace_environ(lexer, &value);
			}
				// fprintf(stderr, "lexer: [%c] [%c] [%c] [%d] [%s]\n", lexer->pc, lexer->c, lexer->nc, in_bracket(lexer->contents, lexer->i), value);
				// fprintf(stderr, "quote: [%c]\n", quote);
			if (!in_bracket(lexer->contents, lexer->i))
			{
				if (ft_strlen(value) == 0 && (lexer->c == quote || lexer->c == ' ' || lexer->c == '\0'))
				{
					lexer_advance(lexer);
					return (init_token(TK_SKIP, value));
				}
				else if (lexer->c != '"')
				{
					value = trim_value(value);
				}
				continue;
			}
			else
			{
				continue;
			}
		}
		s = lexer_get_current_char_as_string(lexer);
		size = ft_strlen(value) + ft_strlen(s) + 1;
		if ((value = ft_realloc(value, size * sizeof(char))) == NULL)
			ft_perror("minishell");
		ft_strlcat(value, s, size);
		free(s);
		lexer_advance(lexer);
	}
	if (!ft_strchr(";|<>", lexer->c))
		lexer_advance(lexer);
	return (init_token(TK_CMD, value));
}
