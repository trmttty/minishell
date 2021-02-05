/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/05 10:05:28 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

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

static char	*trim_value_next(char *value, size_t size)
{
	char		*ret;
	size_t		i;
	size_t		j;

	if ((ret = ft_calloc(size + 1, sizeof(char))) == NULL)
		ft_perror("minishell");
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] != ' ')
			ret[j++] = value[i];
		if (value[i] != ' ' && value[i + 1] == ' ')
			ret[j++] = ' ';
		i++;
	}
	ret[j] = '\0';
	free(value);
	return (ret);
}

char		*trim_value(char *value)
{
	char		*tmp;
	size_t		size;
	size_t		i;

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
	return (trim_value_next(value, size));
}

t_token		*lexer_get_next_checker(t_lexer* lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == ' ' || lexer->c == '\n')
			lexer_skip_whitespace(lexer);
		if (lexer->pc == ' ' && (lexer->c == '"' || lexer->c == '\''))
			return (lexer_collect_string(lexer, lexer->c));
		if (ft_strchr(";<>|", lexer->c))
			return (lexer_advance_with_token(lexer, init_token(TK_RESERVED, lexer_get_current_char_as_string(lexer))));
		return (lexer_collect_string(lexer, 0));
	}
	return (NULL);
}
