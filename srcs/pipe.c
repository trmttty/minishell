/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:19:56 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/02/07 21:00:55 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "evaluate.h"

void	child_pipe(t_node *node, int *flag)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_perror("minishell");
	if ((pid = fork()) == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		exit(evaluate(node->lnode, flag));
	}
	else if (pid < 0)
		ft_perror("minishell");
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
		ft_perror("minishell");
	else
		wait(&status);
	return (status >> 8);
}
