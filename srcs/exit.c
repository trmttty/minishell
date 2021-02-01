/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:33:09 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/01 21:46:47 by kazumanoda       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_num_str(char *str)
{
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int		ft_exit(char **args, t_list **env_lst)
{
	long			rv;

	rv = ft_atoi(get_env("?"));
	if (*args)
	{
		if (!is_num_str(*args))
			exit(255);
		if (args[1])
		{
			fprintf(stderr, "lsh: exit: too many arguments\n");
			return (EXIT_FAILURE);
		}
		rv = ft_atoi(*args);
		rv %= 256;
		if (rv < 0)
			rv += 256;
	}
	exit(rv);
}
