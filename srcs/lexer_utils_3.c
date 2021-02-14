/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/14 03:37:14 by ttarumot         ###   ########.fr       */
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
			&& !(ft_strchr(" \t", lexer->nc) || lexer->nc == '\0')
			&& !lexer->env)
		return (1);
	return (0);
}

int			lexer_escape_string(t_lexer *lexer, char **value)
{
	char	*str;
	size_t	size;

	lexer->escape = 1;
	if (lexer->quote == 0 && lexer->nc == '\n')
	{
		lexer_advance(lexer);
		lexer_advance(lexer);
	}
	else if (lexer->quote == 0)
		lexer_advance(lexer);
	else if (lexer->quote == '"' && ft_strchr("$`\"\\\n", lexer->nc))
		lexer_advance(lexer);
	lexer->escape = 0;
	str = lexer_get_current_char(lexer);
	size = ft_strlen(*value) + ft_strlen(str) + 1;
	if ((*value = ft_realloc(*value, size * sizeof(char))) == NULL)
		ft_perror("minishell");
	ft_strlcat(*value, str, size);
	free(str);
	// if (!lexer->quote && ft_strchr(";|<>", lexer->nc))
	// 	return (1);
	lexer_advance(lexer);
	return (0);
}

char		*lexer_get_exit_code(t_lexer *lexer)
{
	char	*code;

	if ((code = ft_itoa(g_exit_code)) == NULL)
		ft_perror("minishell");
	lexer_advance(lexer);
	lexer_advance(lexer);
	return (code);
}
