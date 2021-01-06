/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:42:39 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/06 20:33:15 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo(char **argv)
{
	int i;
	int n_option;

	i = 0;
	n_option = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "-n", 3) == 0)
		{
			n_option = 1;
		}
		else
		{
			if (i != 0)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(argv[i], 1);
		}
		i++;
	}
	if (n_option == 0)
		ft_putstr_fd("\n", 1);
	return (1);
}
