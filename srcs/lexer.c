/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/02 16:14:53 by ttarumot         ###   ########.fr       */
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
	
	if ((lexer = ft_calloc(1, sizeof(t_lexer))) == NULL)
		ft_perror("minishell");
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	lexer->nc = contents[lexer->i + 1];
	return (lexer);
}

void        lexer_advance(t_lexer* lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->pc = lexer->contents[lexer->i];
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
		lexer->nc = lexer->contents[lexer->i + 1];
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

int		is_escaped(char *s, int pos)
{
	int n;

	n = 0;
	while (pos >= 0 && s[pos] == '\\')
	{
		n++;
		pos--;
	}
	return (n % 2);
}

int		in_bracket(char *s, int pos)
{
	int	bracket1;
	int	bracket2;
	int	i;

	bracket1 = 0;
	bracket2 = 0;
	i = 0;
	while (i <= pos)
	{
		if (s[i] == 34 && (i == 0 || !is_escaped(s, i - 1))
			&& bracket2 % 2 == 0)
			bracket1++;
		if (s[i] == 39 && (i == 0 || bracket2 % 2 != 0 || !is_escaped(s, i - 1))
			&& bracket1 % 2 == 0)
			bracket2++;
		i++;
	}
	if (bracket1 % 2 != 0 || bracket2 % 2 != 0)
		return (1);
	return (0);
}

t_token*    lexer_get_next_token(t_lexer* lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		// fprintf(stderr, "top: [%c] [%c] [%c] [%d]\n", lexer->pc, lexer->c, lexer->nc, in_bracket(lexer->contents, lexer->i));
		if (lexer->c == ' ' || lexer->c == '\n')
			lexer_skip_whitespace(lexer);
		if (lexer->c == ';')
		{
			lexer_advance(lexer);
			return (NULL);
		}
		if (lexer->pc == ' ' && (lexer->c == '"' || lexer->c == '\''))
			return (lexer_collect_string(lexer, lexer->c));
		if (ft_strchr("<>|", lexer->c))
			return (lexer_advance_with_token(lexer, init_token(TK_RESERVED, lexer_get_current_char_as_string(lexer))));
		return (lexer_collect_string(lexer, 0));
	}
	return (NULL);
}

void		replace_environ(t_lexer* lexer, char quote, char **value)
{
	size_t	size;
	size_t	tail;
	size_t	len;
	char	*tmp;
	char	*sub;

	size = ft_strlen(*value);
		tail = 1;
		while (ft_isalnum(lexer->contents[lexer->i + tail]) || lexer->contents[lexer->i + tail] == '_')
			tail++;
		if (lexer->contents[lexer->i + tail] == '?')
			tail++;
		if (tail == 1) 
			sub = ft_substr(&lexer->contents[lexer->i], 0, tail);
		else
		{
			tmp = ft_substr(&lexer->contents[lexer->i], 0, tail);
			sub = get_env(&tmp[1]);
			free(tmp);
		}
		if ((len = ft_strlen(sub)) > 0)
		{
			size += len;
			*value = realloc(*value, (size + 1) * sizeof(char));
			ft_strlcat(*value, sub, size + 1);
		}
		free(sub);
		while (tail--)
			lexer_advance(lexer);
		return ;
}

char		*trim_value(char *value)
{
	size_t		i;
	size_t		j;
	size_t		size;
	char		*tmp;
	char		*ret;

	tmp = value;
	value = ft_strtrim(value, " ");
	free(tmp);
	i = 0;
	size = 0;
	while (value[i])
	{
		if (value[i] != ' ')
			size++;
		if (value[i] != ' ' && value[i + 1] == ' ')
			size++;
		i++;
	}
	ret = ft_calloc(size + 1, sizeof(char));
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] != ' ')
		{
			ret[j++] = value[i];
		}
		if (value[i] != ' ' && value[i + 1] == ' ')
			ret[j++] = ' ';
		i++;
	}
	ret[j] = '\0';
	free(value);
	return (ret);
}

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
			if ((value = realloc(value, size * sizeof(char))) == NULL)
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

		// fprintf(stderr, "lexer: [%c] [%c] [%c] [%d] [%s]\n", lexer->pc, lexer->c, lexer->nc, in_bracket(lexer->contents, lexer->i), value);
		// fprintf(stderr, "quote: [%c]\n", quote);
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
		// fprintf(stderr, "lexer: [%c] [%c] [%c] [%d] [%s]\n", lexer->pc, lexer->c, lexer->nc, in_bracket(lexer->contents, lexer->i), value);
		// fprintf(stderr, "quote: [%c]\n", quote);
		if (lexer->c == '$' && quote != '\'')
		{
			// fprintf(stderr, "lexer: [%c] [%c] [%c] [%d] [%s]\n", lexer->pc, lexer->c, lexer->nc, in_bracket(lexer->contents, lexer->i), value);
			// fprintf(stderr, "quote: [%c]\n", quote);
			while (lexer->c == '$' && quote != '\'')
			{
				replace_environ(lexer, quote, &value);
				// fprintf(stderr, "lexer: [%c] [%c] [%c] [%d] [%s]\n", lexer->pc, lexer->c, lexer->nc, in_bracket(lexer->contents, lexer->i), value);
				// fprintf(stderr, "quote: [%c]\n", quote);
			}
				// fprintf(stderr, "lexer: [%c] [%c] [%c] [%d] [%s]\n", lexer->pc, lexer->c, lexer->nc, in_bracket(lexer->contents, lexer->i), value);
				// fprintf(stderr, "quote: [%c]\n", quote);
			if (!in_bracket(lexer->contents, lexer->i))
			{
				// fprintf(stderr, "lexer: [%c] [%c] [%c] [%d] [%s]\n", lexer->pc, lexer->c, lexer->nc, in_bracket(lexer->contents, lexer->i), value);
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
		if ((value = realloc(value, size * sizeof(char))) == NULL)
			ft_perror("minishell");
		ft_strlcat(value, s, size);
		free(s);
		// if (!in_bracket(lexer->contents, lexer->i) && ft_strchr(";|<>", lexer->nc))
		// {
		// 	break;
		// }
		lexer_advance(lexer);
		// fprintf(stderr, "value1: [%s]\n", value);
	}
	if (!ft_strchr(";|<>", lexer->c))
		lexer_advance(lexer);
	// fprintf(stderr, "lexer: [%c] [%c] [%c]\n", lexer->pc, lexer->c, lexer->nc);
	// fprintf(stderr, "last: [%s]\n", value);
	return (init_token(TK_CMD, value));
}

t_token*    lexer_advance_with_token(t_lexer* lexer, t_token* token)
{
	char	*new_token;

	lexer_advance(lexer);
	if (token->kind == TK_RESERVED && !ft_strcmp(token->value, ">") && lexer->c == '>')
	{
		new_token = ft_strjoin(token->value, ">");
		free(token->value);
		token->value = new_token;
		lexer_advance(lexer);
	}
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
