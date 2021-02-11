/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:18:43 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/11 22:22:08 by kazumanoda       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "signal.h"
#include "evaluate.h"

static int	return_status(int status, char **args)
{
	if (status == 2)
	{
		ft_putstr_fd("\n", 1);
		return (INT_STATUS);
	}
	if (status == 3)
	{
		ft_putstr_fd("^\\Quit: 3\n", 1);
		return (QUIT_STATUS);
	}
	if (status == 256 && args[1])
		return (1);
	if (status == 256)
		return (127);
	return (status >> 8);
}

int			launch(char **args)
{
	pid_t	pid;
	int		status;
	int		rv;

	signal(SIGINT, child_sigint);
	pid = 0;
	status = 0;
	if ((rv = set_cmd_path(args)) != 0)
		return (rv);
	if ((pid = fork()) == 0)
	{
		execve(args[0], args, create_env_vec(g_env_lst));
		ft_perror("minishell");
	}
	else if (pid < 0)
		ft_perror("minishell");
	else
		waitpid(pid, &status, WUNTRACED);
	return (return_status(status, args));
}
