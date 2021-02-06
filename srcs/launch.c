/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:18:43 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/06 14:46:19 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "signal.h"
#include "evaluate.h"
#include "sort_cmd.h"

static char	*find_path(char *relative, char **paths)
{
	char		*absolute;
	char		*dir;
	struct stat	sb;

	if ((absolute = ft_strdup("")) == NULL)
		ft_perror("minishell");
	while (*paths)
	{
		if ((dir = ft_strjoin(*paths, "/")) == NULL)
			ft_perror("minishell");
		free(absolute);
		if ((absolute = ft_strjoin(dir, relative)) == NULL)
			ft_perror("minishell");
		free(dir);
		if (stat(absolute, &sb) == 0)
			return (absolute);
		paths++;
	}
	free(absolute);
	return (NULL);
}

static char	*get_absolute_path(char *relative)
{
	char		**paths;
	char		*env;
	char		*absolute;

	if (ft_strlen(relative) == 0)
		return (NULL);
	env = get_env("PATH");
	if ((paths = ft_split(env, ':')) == NULL)
		ft_perror("minishell");
	free(env);
	absolute = find_path(relative, paths);
	ft_tabfree(paths);
	return (absolute);
}

static int	return_status(int status, char **args)
{
	if (status == 2)
		ft_putstr_fd("\n", 1);
	if (status == 3)
		ft_putstr_fd("^\\Quit: 3\n", 1);
	if (status == 256 && args[1])
		return (1);
	if (status == 256)
		return (127);
	return (status >> 8);
}

int			launch(char **args)
{
	pid_t	pid;
	int		status;
	char	*absolute;

	signal(SIGINT, child_sigint);
	pid = 0;
	status = 0;
	if (**args != '/')
	{
		if ((absolute = get_absolute_path(args[0])) == NULL)
			return (error_status(args[0], NULL, "command not found", 127));
		free(args[0]);
		args[0] = absolute;
	}
	printf("[%s]\n", *args);
	if ((pid = fork()) == 0)
	{
		execve(args[0], args, create_env_vec(g_env_lst));
		ft_perror("minishell");
	}
	else if (pid < 0)
		ft_perror("minishell");
	else
		waitpid(pid, &status, WUNTRACED);
	return (return_status(status, args));
}
