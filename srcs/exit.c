/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:33:09 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/13 01:44:46 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_wspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' \
			|| c == ' ');
}

static long	set_number(char *str, int sign)
{
	long	nb;
	char	*ptr;

	nb = 0;
	ptr = str;
	while (ft_isdigit(*str))
	{
		if (nb == 922337203685477580 && *str >= '8' && sign == 1)
			exit_status("exit", ptr, "numeric argument required", 255);
		if (nb > 922337203685477580 && sign == 1)
			exit_status("exit", ptr, "numeric argument required", 1);
		if (nb == 922337203685477580 && *str >= '9' && sign == -1)
			exit_status("exit", ptr, "numeric argument required", 255);
		if (nb > 922337203685477580 && sign == -1)
			exit_status("exit", ptr, "numeric argument required", 255);
		nb = nb * 10 + (*str++ - '0');
	}
	return (nb);
}

static int	my_atoi(char *str)
{
	int		sign;

	sign = 1;
	while (is_wspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	return ((int)(sign * set_number(str, sign)));
}

static int	is_num_str(char *str)
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

int			ft_exit(char **args)
{
	long	rv;

	rv = g_exit_code;
	ft_putstr_fd("exit\n", 2);
	if (*args)
	{
		if (!is_num_str(*args))
			exit_status("exit", *args, "numeric argument required", 255);
		if (args[1])
			return (error_status("exit", NULL, "too many arguments", 1));
		rv = my_atoi(*args);
		rv %= 256;
		if (rv < 0)
			rv += 256;
	}
	exit(rv);
}
