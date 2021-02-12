/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/13 01:40:17 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

static char	*replace_environ_next(t_lexer *lexer, char **value,
									char *sub, size_t tail)
{
	size_t	len;
	char	*ret;

	ret = NULL;
	if ((len = ft_strlen(sub)) > 0)
	{
		if (lexer->quote)
		{
			if ((*value = ft_realloc(*value,
				(ft_strlen(*value) + len + 1) * sizeof(char))) == NULL)
				ft_perror("minishell");
			ft_strlcat(*value, sub, ft_strlen(*value) + len + 1);
		}
		else
		{
			if ((ret = ft_strdup(sub)) == NULL)
				ft_perror("minishell");
		}
	}
	free(sub);
	while (tail--)
		lexer_advance(lexer);
	return (ret);
}

static char	*lexer_get_env(t_lexer *lexer, size_t tail)
{
	char	*tmp;
	char	*sub;

	if ((tmp = ft_substr(&lexer->contents[lexer->i], 0, tail)) == NULL)
		ft_perror("minishell");
	sub = get_env(&tmp[1]);
	free(tmp);
	return (sub);
}

static char	*replace_environ(t_lexer *lexer, char **value)
{
	char	*sub;
	size_t	tail;

	tail = 1;
	while (ft_isalnum(lexer->contents[lexer->i + tail])
			|| lexer->contents[lexer->i + tail] == '_')
		tail++;
	if (lexer->contents[lexer->i + tail] == '?')
	{
		lexer_advance(lexer);
		lexer_advance(lexer);
		return(ft_itoa(g_exit_code));
	}
	if (tail == 1)
	{
		if (!lexer->quote && (ft_isquote(lexer->contents[lexer->i + tail])))
		{
			lexer_advance(lexer);
			return (NULL);
		}
		if ((sub = ft_substr(&lexer->contents[lexer->i], 0, tail)) == NULL)
			ft_perror("minishell");
	}
	else
		sub = lexer_get_env(lexer, tail);
	return (replace_environ_next(lexer, value, sub, tail));
}

static void	lexer_replace_env(t_lexer *lexer, char **value, char **ret)
{
	char	*env;
	char	*tmp;

	while (lexer->c == '$' && lexer->quote != '\'')
	{
		if ((env = replace_environ(lexer, value)) == NULL)
			continue;
		if (*ret)
		{
			tmp = *ret;
			if ((*ret = ft_strjoin(*ret, env)) == NULL)
				ft_perror("minishell");
			free(env);
			free(tmp);
		}
		else
			*ret = env;
	}
}

int			lexer_expand_env(t_lexer *lexer, char **value)
{
	char	*ret;

	ret = NULL;
	lexer_replace_env(lexer, value, &ret);
	if (((!lexer->quote && !ft_isquote(lexer->c))
		|| (lexer->quote && ft_isquote(lexer->c))))
	{
		if (ft_strlen(*value) == 0 && ret == NULL
			&& (ft_isquote(lexer->c) || ft_strchr(" \t", lexer->c)
				|| lexer->c == '\0'))
			return (1);
		if (ret)
			update_contens(lexer, ret);
	}
	return (0);
}
