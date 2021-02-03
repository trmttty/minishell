/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:19:56 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/02/03 23:42:12 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "evaluate.h"

void	child_pipe(t_node *node, int *flag)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	if ((pid = fork()) == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		exit(evaluate(node->lnode, flag));
	}
	else if (pid < 0)
		perror("lsh");
	else
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		exit(evaluate(node->rnode, flag));
	}
}

int		ft_pipe(t_node *node, int *flag)
{
	int		status;
	pid_t	wpid;

	set_env("_", "");
	flag[0] = 0;
	flag[1] = 0;
	status = 0;
	if ((wpid = fork()) == 0)
		child_pipe(node, flag);
	else if (wpid < 0)
		perror("lsh");
	else
		wait(&status);
	return (status >> 8);
}
