/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:33:09 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/04 15:45:35 by ttarumot         ###   ########.fr       */
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

int		ft_exit(char **args)
{
	long			rv;

	rv = ft_atoi(get_env("?"));
	if (*args)
	{
		if (!is_num_str(*args))
			exit(255);
		if (args[1])
			return (error_status("exit", NULL, "too many arguments", 1));
		rv = ft_atoi(*args);
		rv %= 256;
		if (rv < 0)
			rv += 256;
	}
	exit(rv);
}
