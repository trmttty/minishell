/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:27:13 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/07 00:04:25 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "lexer.h"

t_token		*init_token(t_token_kind type, char *value)
{
	t_token	*token;

	if ((token = calloc(1, sizeof(t_token))) == NULL)
		ft_perror("minishell");
	token->kind = type;
	token->value = value;
	return (token);
}

bool		consume(char *op)
{
	if (g_token->kind != TK_RESERVED || ft_strcmp(g_token->value, op))
		return (false);
	g_token = g_token->next;
	return (true);
}

bool		at_eof(void)
{
	return (g_token->kind == TK_EOF);
}

char		**expect_command(void)
{
	t_token	*tmp;
	char	**cmds;
	size_t	size;
	size_t	i;

	tmp = g_token;
	size = 0;
	while (tmp->kind == TK_CMD)
	{
		size++;
		tmp = tmp->next;
	}
	if ((cmds = ft_calloc(size + 1, sizeof(char*))) == NULL)
		ft_perror(NULL);
	i = 0;
	while (g_token->kind == TK_CMD)
	{
		cmds[i] = ft_strdup(g_token->value);
		if (cmds[i] == NULL)
			ft_perror("minishell");
		g_token = g_token->next;
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

void		free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		free(token->value);
		tmp = token;
		token = token->next;
		free(tmp);
	}
}
