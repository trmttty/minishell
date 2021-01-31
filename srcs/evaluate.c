/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:55:18 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/31 22:01:58 by kazumanoda       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "evaluate.h"

int		ft_exe(char **args)
{
	t_list		**env_lst;

	if (args[0] != NULL)
	{
		if (ft_strcmp(args[0], "echo") == 0)
			return (ft_echo(&args[1], env_lst));
		else if (ft_strcmp(args[0], "cd") == 0)
			return (ft_cd(&args[1], env_lst));
		else if (ft_strcmp(args[0], "export") == 0)
			return (ft_export(&args[1], env_lst));
		else if (ft_strcmp(args[0], "unset") == 0)
			return (ft_unset(&args[1], env_lst));
		else if (ft_strcmp(args[0], "pwd") == 0)
			return (ft_pwd(&args[1], env_lst));
		else if (ft_strcmp(args[0], "env") == 0)
			return (ft_env(&args[1], env_lst));
		else if (ft_strcmp(args[0], "exit") == 0)
			return (ft_exit(&args[1], env_lst));
	}
	return (launch(args));
}

int		ft_colon(t_node *node, int *flag)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	if ((wpid = fork()) == 0)
	{
		if ((pid = fork()) == 0)
			exit(evaluate(node->lnode, flag));
		else if (wpid < 0)
			perror("lsh");
		else
		{
			wait(NULL);
			exit(evaluate(node->rnode, flag));
		}
	}
	else if (wpid < 0)
		perror("lsh");
	else
		wait(&status);
	return (status);
}

int		evaluate(t_node *node, int *flag)
{
	if (node->commands != NULL)
		return (ft_exe(node->commands));
	if (ft_strcmp(node->operation, "|") == 0)
		return (ft_pipe(node, flag));
	if (ft_strcmp(node->operation, ";") == 0)
		return (ft_colon(node, flag));
	if (ft_strcmp(node->operation, ">") == 0)
		return (ft_redirect_out(node, flag));
	if (ft_strcmp(node->operation, ">>") == 0)
		return (ft_redirect_outout(node, flag));
	if (ft_strcmp(node->operation, "<") == 0)
		return (ft_redirect_in(node, flag));
	return (0);
}
