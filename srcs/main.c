/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:38:26 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/06 21:05:39 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute(char **args)
{
	int		i;

	if (ft_strncmp(args[0], "echo", 5) == 0)
		return (echo(&args[1]));
	return (0);
}

void	loop(void)
{
	char	*line;
	char	**args;
	int		status;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		get_next_line(0, &line);
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue;
		}
		args = ft_split(line, ' ');
		status = execute(args);
		if (status == 0)
		{
			ft_putstr_fd("minishell: command not found: ", 1);
			ft_putstr_fd(args[0], 1);
			ft_putstr_fd("\n", 1);
		}
		free(line);
		ft_tabfree(args);
	}
}

int		main(int argc, char **argv)
{
	loop();
	return (0);
}
