/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:14:01 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/04 22:54:55 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status(char *commnad, char *arg, char *message, int code)
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

int		error_status(char *commnad, char *arg, char *message, int code)
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
	return (code);
}

void	ft_perror(char *message)
{
	if (message)
		ft_putstr_fd(message, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	exit(EXIT_FAILURE);
}
