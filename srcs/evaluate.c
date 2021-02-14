/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:55:18 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/14 15:02:06 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "evaluate.h"
#include "lexer.h"

static char	**expand_command(t_node *node)
{
	char	**args;

	args = lexer_expand_command(node->commands);
	node->expand = 1;
	ft_tabfree(node->commands);
	node->commands = args;
	return (args);
}

int			ft_exe(t_node *node)
{
	char	**args;

	args = expand_command(node);
	if (*args == NULL)
		return (0);
	set_env("_", args[ft_tabsize(args) - 1]);
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(&args[1]));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(&args[1]));
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(&args[1]));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(&args[1]));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(&args[1]));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(&args[1]));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(&args[1]));
	return (launch(args));
}

int			evaluate(t_node *node, int *flag)
{
	if (node->commands != NULL)
		return (ft_exe(node));
	if (ft_strcmp(node->operation, "|") == 0)
		return (ft_pipe(node, flag));
	if (create_redirect(node, flag) == 1)
		return (EXIT_FAILURE);
	if (ft_strcmp(node->operation, ">") == 0)
		return (ft_redirect_out(node, flag));
	if (ft_strcmp(node->operation, ">>") == 0)
		return (ft_redirect_outout(node, flag));
	if (ft_strcmp(node->operation, "<") == 0)
		return (ft_redirect_in(node, flag));
	return (EXIT_SUCCESS);
}
