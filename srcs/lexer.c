/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/24 11:28:06 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

t_lexer*    init_lexer(char* contents)
{
	t_lexer* lexer;
	
	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

void        lexer_advance(t_lexer* lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

// whitespace?????
void        lexer_skip_whitespace(t_lexer* lexer)
{
	while (lexer->c == ' ' || lexer->c == '\n')
	{
		lexer_advance(lexer);
	}
}

t_token*    lexer_get_next_token(t_lexer* lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == ' ' || lexer->c == '\n')
			lexer_skip_whitespace(lexer);
		if (lexer->c == '"' || lexer->c == '\'')
			return (lexer_collect_string(lexer, lexer->c));
		if (ft_strchr(";()<>|", lexer->c))
			return (lexer_advance_with_token(lexer, init_token(TK_RESERVED, lexer_get_current_char_as_string(lexer))));
		return (lexer_collect_id(lexer));
	}
	return (NULL);
}

t_token*    lexer_collect_string(t_lexer* lexer, char quote)
{
	char    *value;
	char    *s;
	size_t  size;

	lexer_advance(lexer);
	value = calloc(1, sizeof(char));
	value[0] = '\0';
	while (lexer->c != quote)
	{
		s = lexer_get_current_char_as_string(lexer);
		size = ft_strlen(value) + ft_strlen(s) + 1;
		value = realloc(value, size * sizeof(char));
		ft_strlcat(value, s, size);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (init_token(TK_CMD, value));
}

t_token*    lexer_collect_id(t_lexer* lexer)
{
	char*   value;
	char*   s;
	int		quote;
	size_t  size;
	
	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	quote = -1;
	while (!(ft_strchr(";()<>|", lexer->c) || lexer->c == ' '))
	{
		if (lexer->c == '\\')
		{
			s = lexer_get_current_char_as_string(lexer);
			size = ft_strlen(value) + ft_strlen(s) + 1;
			value = realloc(value, size * sizeof(char));
			ft_strlcat(value, s, size);
			lexer_advance(lexer);
			free(s);
			s = lexer_get_current_char_as_string(lexer);
			size = ft_strlen(value) + ft_strlen(s) + 1;
			value = realloc(value, size * sizeof(char));
			ft_strlcat(value, s, size);
			lexer_advance(lexer);
			free(s);
		}
		else if (lexer->c == '"' || lexer->c == '\'')
		{
			t_token *t;
			t = lexer_collect_string(lexer, lexer->c);
			s = value;
			value = ft_strjoin(value, t->value);
			free(s);
		}
		else
		{
			s = lexer_get_current_char_as_string(lexer);
			size = ft_strlen(value) + ft_strlen(s) + 1;
			value = realloc(value, size * sizeof(char));
			ft_strlcat(value, s, size);
			lexer_advance(lexer);
			free(s);
		}
	}
	return (init_token(TK_CMD, value));
}

t_token*    lexer_advance_with_token(t_lexer* lexer, t_token* token)
{
	lexer_advance(lexer);
	return (token);
}

char* lexer_get_current_char_as_string(t_lexer* lexer)
{
	char*	str;
	
	str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
