/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/15 13:09:40 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

char		**create_command_vec(t_list *command_lst)
{
	char	**command_vec;
	t_list	*tmp;
	int		size;
	int		i;

	tmp = command_lst;
	size = ft_lstsize(command_lst);
	if ((command_vec = ft_calloc(size + 1, sizeof(char*))) == NULL)
		ft_perror("minishell");
	i = 0;
	while (i < size)
	{
		if ((command_vec[i] = ft_strdup(tmp->content)) == NULL)
			ft_perror("minishell");
		i++;
		tmp = tmp->next;
	}
	command_vec[i] = NULL;
	ft_lstclear(&command_lst, free);
	return (command_vec);
}

char		**lexer_expand_command(char **commands)
{
	t_lexer	*lexer;
	t_token	*token;
	t_list	*command_lst;

	command_lst = NULL;
	while (*commands)
	{
		lexer = new_lexer(*commands, 0);
		while ((token = lexer_get_next_token(lexer)) != NULL)
		{
			if (token->kind != TK_SKIP)
			{
				ft_lstadd_back(&command_lst,
								ft_lstnew(ft_strdup(token->value)));
			}
			free(token->value);
			free(token);
		}
		free_lexer(lexer);
		commands++;
	}
	return (create_command_vec(command_lst));
}

char		**lexer_expand_file_name(char **commands)
{
	t_lexer	*lexer;
	t_token	*token;
	t_list	*command_lst;

	command_lst = NULL;
	while (*commands)
	{
		lexer = new_lexer(*commands, 0);
		while ((token = lexer_get_next_token(lexer)) != NULL)
		{
			if (token->kind == TK_SKIP)
			{
				free(token->value);
				free(token);
				free_lexer(lexer);
				return (NULL);
			}
			ft_lstadd_back(&command_lst, ft_lstnew(ft_strdup(token->value)));
			free(token->value);
			free(token);
		}
		free_lexer(lexer);
		commands++;
	}
	return (create_command_vec(command_lst));
}
