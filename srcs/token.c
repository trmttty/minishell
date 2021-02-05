/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:27:13 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/05 09:07:20 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "lexer.h"

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

t_token		*new_token(t_token_kind kind, t_token *cur, char *value)
{
	t_token	*token;

	if ((token = ft_calloc(1, sizeof(t_token))) == NULL)
		ft_perror("minishell");
	token->kind = kind;
	if (value != NULL)
		token->value = ft_strdup(value);
	cur->next = token;
	return (token);
}

t_token		*generate_token(t_lexer *lexer)
{
	t_token		*token;
	t_token		token_head;
	t_token		*cur;

	token_head.next = NULL;
	cur = &token_head;
	while ((token = lexer_get_next_token(lexer)) != NULL)
	{
		if (token->kind != TK_SKIP)
			cur = new_token(token->kind, cur, token->value);
		free(token->value);
		free(token);
	}
	if (token_head.next)
		new_token(TK_EOF, cur, NULL);
	return (token_head.next);
}
