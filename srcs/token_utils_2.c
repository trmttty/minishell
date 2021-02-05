/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:27:13 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/05 15:49:40 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "lexer.h"

void		swap_token(t_token *token)
{
	t_token_kind	tmp_kind;
	char			*tmp_value;

	tmp_kind = token->next->next->kind;
	tmp_value = token->next->next->value;
	token->next->next->kind = token->next->kind;
	token->next->next->value = token->next->value;
	token->next->kind = token->kind;
	token->next->value = token->value;
	token->kind = tmp_kind;
	token->value = tmp_value;
}

void		sort_token(void)
{
	t_token			*tmp;
	int				swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		tmp = g_token;
		while (tmp->kind != TK_EOF)
		{
			if ((!ft_strcmp(tmp->value, ">") || !ft_strcmp(tmp->value, ">>")
				|| !ft_strcmp(tmp->value, "<"))
				&& tmp->next->value && tmp->next->kind == TK_CMD
				&& tmp->next->next->value && tmp->next->next->kind == TK_CMD)
			{
				swap_token(tmp);
				swapped = 1;
			}
			tmp = tmp->next;
		}
	}
}

t_token		*generate_checker(t_lexer *lexer)
{
	t_token		*token;
	t_token		token_head;
	t_token		*cur;

	token_head.next = NULL;
	cur = &token_head;
	while ((token = lexer_get_next_checker(lexer)) != NULL)
	{
		cur = new_token(token->kind, cur, token->value);
		free(token->value);
		free(token);
	}
	if (token_head.next)
		new_token(TK_EOF, cur, NULL);
	return (token_head.next);
}

int			syntax_check(t_token *token)
{
	if (!ft_strcmp(token->value, ";") || !ft_strcmp(token->value, "|"))
		return (0);
	while (token->next)
	{
		if ((!ft_strcmp(token->value, ";") || !ft_strcmp(token->value, "|"))
			&& token->next->kind != TK_EOF
			&& ((!ft_strcmp(token->next->value, ";")
			|| !ft_strcmp(token->next->value, "|"))))
			return (0);
		if ((!ft_strcmp(token->value, ">") || !ft_strcmp(token->value, ">>")
			|| !ft_strcmp(token->value, "<"))
			&& token->next->kind == TK_RESERVED)
			return (0);
		if ((!ft_strcmp(token->value, ">") && token->next->kind == TK_EOF))
			return (0);
		if ((!ft_strcmp(token->value, ">>") && token->next->kind == TK_EOF))
			return (0);
		if ((!ft_strcmp(token->value, "<") && token->next->kind == TK_EOF))
			return (0);
		if ((!ft_strcmp(token->value, "|") && token->next->kind == TK_EOF))
			return (0);
		token = token->next;
	}
	return (1);
}

int			check_syntax(char *line)
{
	t_token *token;
	t_lexer	*lexer;
	int		ret;

	if (in_bracket(line, ft_strlen(line) - 1))
		return (error_status(NULL, NULL, "syntax error", 0));
	lexer = new_lexer(line);
	ret = 0;
	if ((token = generate_checker(lexer)) != NULL)
	{
		ret = syntax_check(token);
		free_token(token);
	}
	free(lexer);
	if (ret)
		return (1);
	return (error_status(NULL, NULL, "syntax error", 0));
}
