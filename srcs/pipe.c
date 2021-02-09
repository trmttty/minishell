/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:19:56 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/02/09 19:57:57 by kazumanoda       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "evaluate.h"

void	pipe_out(t_node *node, int *flag, int *fildes)
{
	dup2(fildes[1], 1);
	close(fildes[0]);
	close(fildes[1]);
	exit(evaluate(node->lnode, flag));
}

void	pipe_in(t_node *node, int *flag, int *fildes)
{
	dup2(fildes[0], 0);
	close(fildes[0]);
	close(fildes[1]);
	exit(evaluate(node->rnode, flag));
}

void	pipe_wait(pid_t wpid, pid_t pid, int *fildes, int *status)
{
	close(fildes[0]);
	close(fildes[1]);
	waitpid(wpid, status, WUNTRACED);
	waitpid(pid, NULL, WUNTRACED);
}

int		ft_pipe(t_node *node, int *flag)
{
	int		status;
	pid_t	wpid;
	pid_t	pid;
	int		fildes[2];

	flag[0] = 0;
	flag[1] = 0;
	status = 0;
	pipe(fildes);
	if ((pid = fork()) == 0)
		pipe_out(node, flag, fildes);
	else if (pid < 0)
		ft_perror("minishell");
	else
	{
		if ((wpid = fork()) == 0)
			pipe_in(node, flag, fildes);
		else if (pid < 0)
			ft_perror("minishell");
		else
			pipe_wait(wpid, pid, fildes, &status);
	}
	return (status >> 8);
}
