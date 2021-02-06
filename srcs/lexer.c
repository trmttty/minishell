/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/07 00:03:50 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

int			ft_isescape(t_lexer *lexer)
{
	if (lexer->c == '\\' && lexer->quote != '\'')
	{
		if (lexer->quote == 0)
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
		if (lexer->quote && lexer->quote == lexer->c && !lexer->env)
		{
			// fprintf(stderr, "lexer: [%c] [%c] [%c] [%c] [%s]\n", lexer->pc, lexer->c, lexer->nc, lexer->quote, value);
			lexer_advance(lexer);
		}	
		else if (!lexer->quote && ft_isquote(lexer->c) && !(lexer->nc == ' ' || lexer->nc == '\0') && !lexer->env)
		{
			// fprintf(stderr, "lexer: [%c] [%c] [%c] [%c] [%s]\n", lexer->pc, lexer->c, lexer->nc, lexer->quote, value);
			lexer_advance(lexer);
		}
		else if (!lexer->quote && (ft_strchr(";|<>", lexer->c) || ft_isquote(lexer->c)) && !lexer->env)
		{
			break;
		}
		else if (!lexer->quote && ft_strchr(" \t", lexer->c))
		{
			break;
		}
		else if (ft_isescape(lexer) && !lexer->env)
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
		else if (lexer->c == '$' && lexer->quote != '\'' && !lexer->env)
		{
			while (lexer->c == '$' && lexer->quote != '\'')
			{
				replace_environ(lexer, &value);
			}
			// fprintf(stderr, "lexer: [%c] [%c] [%c] [%c] [%s]\n", lexer->pc, lexer->c, lexer->nc, lexer->quote, value);
				// fprintf(stderr, "quote: [%c]\n", quote);
			if (!lexer->quote && !ft_isquote(lexer->c) && ft_strcmp(value, "$"))
			{
				if (ft_strlen(value) == 0 && (ft_isquote(lexer->c) || ft_strchr(" \t", lexer->c) || lexer->c == '\0'))
				{
					lexer_advance(lexer);
					return (init_token(TK_SKIP, value));
				}
				char *tmp;
				tmp = lexer->contents;
				if (ft_isquote(lexer->c))
					lexer->i++;
				lexer->env = ft_strlen(value);
				lexer->contents = ft_strjoin(value, &lexer->contents[lexer->i]);
				free(tmp);
				free(value);
				value = ft_strdup("");
				lexer->i = 0;
				lexer->pc = 0;
				lexer->c = lexer->contents[0];
				if (ft_strlen(lexer->contents))
					lexer->nc = lexer->contents[1];
				else
					lexer->nc = 0;
				while (!lexer->quote && (lexer->c == ' ' || lexer->c == '\t'))
					lexer_skip_whitespace(lexer);
				
				// if (ft_strlen(value) == 0 && (ft_isquote(lexer->c) || ft_strchr(" \t", lexer->c) || lexer->c == '\0'))
				// {
				// 	lexer_advance(lexer);
				// 	return (init_token(TK_SKIP, value));
				// }
				// else if (lexer->c != '"')
				// {
				// 	value = trim_value(value);
				// }
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
