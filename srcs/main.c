/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:38:26 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/07 03:31:03 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute(char **args, char **envp)
{
	int		i;

	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(&args[1], envp));
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(&args[1], envp));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(&args[1], envp));
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(&args[1], envp));
	if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(&args[1], envp));
	return (0);
}

void	loop(char **envp)
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
		status = execute(args, envp);
		free(line);
		ft_tabfree(args);
		if (status == 0)
			break;
	}
}

int		main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	loop(envp);
	return (0);
}
