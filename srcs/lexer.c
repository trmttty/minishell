/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/06 11:16:35 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

int			ft_isescape(t_lexer *lexer)
{
	if (lexer->c == '\\' && lexer->quote != '\'')
	{
		if (lexer->quote == 0 && lexer->nc == '\n')
		{
			// ++2
			return (1);
		}
		if (lexer->quote == 0)
		{
			// ++1
			return (1);
		}
		if (lexer->quote == '"' && ft_strchr("$`\"\\\n", lexer->nc))
		{
			// ++1
			return (1);
		}
	}	
	return (0);
}

t_token*    lexer_collect_string(t_lexer* lexer)
{
	char    *value;
	char    *s;
	size_t  size;

	if ((value = ft_calloc(1, sizeof(char))) == NULL)
		ft_perror("minishell");
	value[0] = '\0';
	while (lexer->c != '\0')
	{
		if (lexer->quote && lexer->quote == lexer->c)
		{
			// fprintf(stderr, "lexer: [%c] [%c] [%c] [%c] [%s]\n", lexer->pc, lexer->c, lexer->nc, lexer->quote, value);
			lexer_advance(lexer);
		}	
		else if (!lexer->quote && ft_isquote(lexer->c) && !(lexer->nc == ' ' || lexer->nc == '\0'))
		{
			// fprintf(stderr, "lexer: [%c] [%c] [%c] [%c] [%s]\n", lexer->pc, lexer->c, lexer->nc, lexer->quote, value);
			lexer_advance(lexer);
		}
		else if (!lexer->quote && (ft_strchr(";|<>", lexer->c) || ft_isquote(lexer->c) || ft_strchr(" \t", lexer->c)))
		{
			break;
		}
		else if (ft_isescape(lexer))
		{
			if (lexer->quote == 0 && lexer->nc == '\n')
			{
				lexer_advance(lexer);
				lexer_advance(lexer);
				break;
			}
			else if (lexer->quote == 0)
			{
				lexer_advance(lexer);
			}
			else if (lexer->quote == '"' && ft_strchr("$`\"\\\n", lexer->nc))
			{
				lexer_advance(lexer);
			}
			s = lexer_get_current_char(lexer);
			size = ft_strlen(value) + ft_strlen(s) + 1;
			if ((value = ft_realloc(value, size * sizeof(char))) == NULL)
				ft_perror("minishell");
			ft_strlcat(value, s, size);
			free(s);
			if (!lexer->quote && ft_strchr(";|<>", lexer->nc))
			{
				break;
			}
			lexer_advance(lexer);
		}
		else if (lexer->c == '$' && lexer->quote != '\'')
		{
			while (lexer->c == '$' && lexer->quote != '\'')
			{
				replace_environ(lexer, &value);
			}
			// fprintf(stderr, "lexer: [%c] [%c] [%c] [%d] [%s]\n", lexer->pc, lexer->c, lexer->nc, in_bracket(lexer), value);
				// fprintf(stderr, "quote: [%c]\n", quote);
			if (!lexer->quote)
			{
				if (ft_strlen(value) == 0 && (ft_isquote(lexer->c) || ft_strchr(" \t", lexer->c) || lexer->c == '\0'))
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
		else
		{
			s = lexer_get_current_char(lexer);
			size = ft_strlen(value) + ft_strlen(s) + 1;
			if ((value = ft_realloc(value, size * sizeof(char))) == NULL)
			ft_perror("minishell");
			ft_strlcat(value, s, size);
			free(s);
			lexer_advance(lexer);
		}
	}
	if (!ft_strchr(";|<>", lexer->c))
		lexer_advance(lexer);
	return (init_token(TK_CMD, value));
}
