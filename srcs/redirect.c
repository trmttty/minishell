/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:20:00 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/02/04 12:29:22 by ttarumot         ###   ########.fr       */
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
		fd = open(node->rnode->commands[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (flag[0] == 0)
		{
			dup2(fd, STDOUT_FILENO);
			flag[0] = 1;
		}
		exit(evaluate(node->lnode, flag));
	}
	else if (pid < 0)
		perror("lsh");
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
		fd = open(node->rnode->commands[0], \
		O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (flag[0] == 0)
		{
			dup2(fd, STDOUT_FILENO);
			flag[0] = 1;
		}
		exit(evaluate(node->lnode, flag));
	}
	else if (pid < 0)
		perror("lsh");
	else
		wait(&status);
	return (status >> 8);
}

int		ft_redirect_in(t_node *node, int *flag)
{
	int		fd;

	fd = open(node->rnode->commands[0], O_RDONLY);
	if (flag[1] == 0)
	{
		dup2(fd, STDIN_FILENO);
		flag[1] = 1;
	}
	return (evaluate(node->lnode, flag));
}
