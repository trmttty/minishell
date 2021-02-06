/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/07 02:17:58 by ttarumot         ###   ########.fr       */
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
			return (1);
		if (lexer->quote == '"' && ft_strchr("$`\"\\\n", lexer->nc))
			return (1);
	}	
	return (0);
}

int			lexer_skip_quote(t_lexer *lexer)
{
	if (lexer->quote && lexer->quote == lexer->c && !lexer->env)
		return (1);
	else if (!lexer->quote && ft_isquote(lexer->c)
			&& !(lexer->nc == ' ' || lexer->nc == '\0') && !lexer->env)
		return (1);
	return (0);
}

int			lexer_return_string(t_lexer *lexer)
{
	if (!lexer->quote && (ft_strchr(";|<>", lexer->c)
		|| ft_isquote(lexer->c)) && !lexer->env)
		return (1);
	else if (!lexer->quote && ft_strchr(" \t", lexer->c))
		return (1);
	return (0);
}

int			lexer_escape_string(t_lexer *lexer, char **value)
{
	char    *str;
	size_t  size;

	if (lexer->quote == 0 && lexer->nc == '\n')
	{
		lexer_advance(lexer);
		lexer_advance(lexer);
	}
	else if (lexer->quote == 0)
		lexer_advance(lexer);
	else if (lexer->quote == '"' && ft_strchr("$`\"\\\n", lexer->nc))
		lexer_advance(lexer);
	str = lexer_get_current_char(lexer);
	size = ft_strlen(*value) + ft_strlen(str) + 1;
	if ((*value = ft_realloc(*value, size * sizeof(char))) == NULL)
		ft_perror("minishell");
	ft_strlcat(*value, str, size);
	free(str);
	if (!lexer->quote && ft_strchr(";|<>", lexer->nc))
		return (1);
	lexer_advance(lexer);
	return (0);
}

int			lexer_expand_env(t_lexer *lexer, char **value)
{
	char *tmp;

	while (lexer->c == '$' && lexer->quote != '\'')
		replace_environ(lexer, value);
	if (!lexer->quote && !ft_isquote(lexer->c) && ft_strcmp(*value, "$"))
	{
		if (ft_strlen(*value) == 0 && (ft_isquote(lexer->c) || ft_strchr(" \t", lexer->c) || lexer->c == '\0'))
			return (1);
		tmp = lexer->contents;
		if (ft_isquote(lexer->c))
			lexer->i++;
		lexer->env = ft_strlen(*value);
		lexer->contents = ft_strjoin(*value, &lexer->contents[lexer->i]);
		free(tmp);
		free(*value);
		*value = ft_strdup("");
		lexer->i = 0;
		lexer->pc = 0;
		lexer->c = lexer->contents[0];
		if (ft_strlen(lexer->contents))
			lexer->nc = lexer->contents[1];
		else
			lexer->nc = 0;
		while (!lexer->quote && (lexer->c == ' ' || lexer->c == '\t'))
			lexer_skip_whitespace(lexer);
	}
	return (0);
}

void		lexer_collect_current_char(t_lexer *lexer, char **value)
{
	char    *s;
	size_t  size;

	s = lexer_get_current_char(lexer);
	size = ft_strlen(*value) + ft_strlen(s) + 1;
	if ((*value = ft_realloc(*value, size * sizeof(char))) == NULL)
	ft_perror("minishell");
	ft_strlcat(*value, s, size);
	free(s);
	lexer_advance(lexer);
}

t_token*    lexer_collect_string(t_lexer *lexer)
{
	char    *value;

	if ((value = ft_calloc(1, sizeof(char))) == NULL)
		ft_perror("minishell");
	while (lexer->c != '\0')
	{
		if (lexer_skip_quote(lexer))
			lexer_advance(lexer);
		else if (lexer_return_string(lexer))
			break;
		else if (ft_isescape(lexer) && !lexer->env)
		{
			if (lexer_escape_string(lexer, &value))
				break;
		}
		else if (lexer->c == '$' && lexer->quote != '\'' && !lexer->env)
		{
			if (lexer_expand_env(lexer, &value))
			{
				lexer_advance(lexer);
				return (init_token(TK_SKIP, value));
			}
		}
		else
			lexer_collect_current_char(lexer, &value);
	}
	if (!ft_strchr(";|<>", lexer->c))
		lexer_advance(lexer);
	return (init_token(TK_CMD, value));
}
