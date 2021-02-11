/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:20:00 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/02/12 00:24:47 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "evaluate.h"

int		ft_redirect_out(t_node *node, int *flag)
{
	pid_t	pid;
	int		status;
	int		fd;

	status = 0;
	if ((pid = fork()) == 0)
	{
		if ((fd = open(node->rnode->commands[0], \
		O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
			ft_perror("minishell");
		if (flag[0] == 0)
		{
			dup2(fd, STDOUT_FILENO);
			flag[0] = 1;
		}
		exit(evaluate(node->lnode, flag));
	}
	else if (pid < 0)
		ft_perror("minishell");
	else
		wait(&status);
	return (status >> 8);
}

int		ft_redirect_outout(t_node *node, int *flag)
{
	pid_t	pid;
	int		status;
	int		fd;

	status = 0;
	if ((pid = fork()) == 0)
	{
		if ((fd = open(node->rnode->commands[0], \
		O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
			ft_perror("minishell");
		if (flag[0] == 0)
		{
			dup2(fd, STDOUT_FILENO);
			flag[0] = 1;
		}
		exit(evaluate(node->lnode, flag));
	}
	else if (pid < 0)
		ft_perror("minishell");
	else
		wait(&status);
	return (status >> 8);
}

void	dup_stdin(t_node *node, int *flag)
{
	int		fd;

	if ((fd = open(node->rnode->commands[0], O_RDONLY)) == -1)
		ft_perror("minishell");
	if (flag[1] == 0)
	{
		dup2(fd, STDIN_FILENO);
		flag[1] = 1;
	}
	exit(evaluate(node->lnode, flag));
}

int		ft_redirect_in(t_node *node, int *flag)
{
	pid_t	pid;
	int		status;

	// if (node->lnode->commands[0] && \
	// ft_strcmp(node->lnode->commands[0], "exit") == 0)
	// dup_stdin(node, flag);
	status = 0;
	pid = fork();
	if (pid == 0)
		dup_stdin(node, flag);
	else if (pid < 0)
		ft_perror("minishell");
	else
		wait(&status);
	return (status >> 8);
}
