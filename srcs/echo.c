/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:42:39 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/08 20:18:34 by kazumanoda       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		option_check(char *str)
{
	if (*str == '-' && *(++str))
	{
		while (*str)
		{
			if (*str == 'n')
				str++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

int		ft_echo(char **args)
{
	int i;
	int n_option;

	i = 0;
	n_option = 0;
	while (*args)
	{
		if (option_check(*args))
			n_option = 1;
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
	return (0);
}
