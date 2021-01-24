/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:42:39 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/24 13:37:13 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **args, t_list **env_lst)
{
	int i;
	int n_option;

	i = 0;
	n_option = 0;
	while (*args)
	{
		if (ft_strcmp(*args, "-n") == 0)
		{
			n_option = 1;
		}
		else
		{
			if (i != 0)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(*args, 1);
			i++;
		}
		args++;
	}
	if (n_option == 0)
		ft_putstr_fd("\n", 1);
	return (1);
}
