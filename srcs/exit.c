/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:33:09 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/22 15:53:34 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_exit(char **args, t_list **env_lst)
{
	int	exit_code;
	int	num;

	exit_code = 0;
	ft_putendl_fd("exit", 2);
	if (*args)
	{
		if (ft_tabsize(args) > 1)
			exit_code = 1;
		else
			exit_code = ft_atoi(*args);
	}
	else
	{
		exit_code = ft_atoi(get_env("?"));
	}
	exit(exit_code % 256);
}
