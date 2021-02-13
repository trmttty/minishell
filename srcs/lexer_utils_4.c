/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/13 12:08:39 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

int			lexer_return_string(t_lexer *lexer)
{
	if (!lexer->quote && (ft_strchr(";|<>", lexer->c)
		|| ft_isquote(lexer->c)) && !lexer->env)
		return (1);
	else if (!lexer->quote && ft_strchr(" \t", lexer->c))
		return (1);
	return (0);
}

void		lexer_collect_current_char(t_lexer *lexer, char **value)
{
	char	*s;
	size_t	size;

	s = lexer_get_current_char(lexer);
	size = ft_strlen(*value) + ft_strlen(s) + 1;
	if ((*value = ft_realloc(*value, size * sizeof(char))) == NULL)
		ft_perror("minishell");
	ft_strlcat(*value, s, size);
	free(s);
	lexer_advance(lexer);
}

t_token		*lexer_loop(t_lexer *lexer, char **value)
{
	while (lexer->c != '\0')
	{
		if (lexer_skip_quote(lexer))
			lexer_advance(lexer);
		else if (lexer_return_string(lexer))
			break ;
		else if (ft_isescape(lexer) && !lexer->env)
		{
			if (lexer_escape_string(lexer, value))
				break ;
		}
		else if (lexer->c == '$' && lexer->quote != '\'' && !lexer->env)
		{
			if (lexer_expand_env(lexer, value))
			{
				lexer_advance(lexer);
				return (init_token(TK_SKIP, *value));
			}
		}
		else
			lexer_collect_current_char(lexer, value);
	}
	return (NULL);
}

t_token		*lexer_collect_string(t_lexer *lexer)
{
	char	*value;
	t_token	*token;

	if ((value = ft_calloc(1, sizeof(char))) == NULL)
		ft_perror("minishell");
	if ((token = lexer_loop_raw(lexer, &value)) != NULL)
		return (token);
	if (!ft_strchr(";|<>", lexer->c))
		lexer_advance(lexer);
	return (init_token(TK_CMD, value));
}

void		update_contens(t_lexer *lexer, char *value)
{
	char	*tmp;

	tmp = lexer->contents;
	if (lexer->quote && ft_isquote(lexer->c))
		lexer->quote = 0;
	lexer->env = ft_strlen(value);
	lexer->contents = ft_strjoin(value, &lexer->contents[lexer->i]);
	free(tmp);
	free(value);
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
