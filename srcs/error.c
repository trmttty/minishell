/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:14:01 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/31 20:51:46 by kazumanoda       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_failure(char *commnad, char *arg, char *message, int code)
{
	ft_putendl_fd("minishell: ", 2);
	if (commnad)
	{
		ft_putendl_fd(commnad, 2);
		ft_putendl_fd(": ", 2);
	}
	if (arg)
	{
		ft_putendl_fd(arg, 2);
		ft_putendl_fd(": ", 2);
	}
	if (message)
	{
		ft_putendl_fd(message, 2);
	}
	ft_putendl_fd("\n", 2);
	exit(code);
}

int		return_with_failure(char *commnad, char *arg, char *message, int code)
{
	ft_putstr_fd("minishell: ", 2);
	if (commnad)
	{
		ft_putstr_fd(commnad, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (message)
	{
		ft_putstr_fd(message, 2);
	}
	ft_putstr_fd("\n", 2);
	return(code);
}

// void	set_exit_status(int code)
// {
// 	char **args;

// 	if ((args = ft_calloc(2, sizeof(char*))) == NULL)
// 		exit(1);
// 	// args
// 	// ft_export(ft_split("?=255", ' '), &g_env_lst);
// }

void	handle_error(char *message)
{
	exit(1);
}
