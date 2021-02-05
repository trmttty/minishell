/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:18:43 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/05 10:20:26 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "signal.h"
#include "evaluate.h"
#include "sort_cmd.h"

char	*get_absolute_path(char *relative)
{
	char		**paths;
	char		**tmp;
	char		*dir;
	char		*env;
	char		*absolute;
	struct stat	sb;

	env = get_env("PATH");
	if ((paths = ft_split(env, ':')) == NULL)
		ft_perror("minishell");
	free(env);
	tmp = paths;
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
		if (stat(absolute , &sb) == 0)
			break;
		paths++;
	}
	ft_tabfree(tmp);
	return (absolute);
}

int		launch(char **args)
{
    pid_t	pid;
	pid_t	wpid;
    int		status;
	char	*tmp;

    signal(SIGINT, child_sigint);
	pid = 0;
	status = 0;
	if (**args != '/')
	{
		tmp = args[0];
		if ((args[0] = get_absolute_path(args[0])) != NULL)
			set_env("_", args[0]);
		free(tmp);
	}
    if ((pid = fork()) == 0)
	{
        execve(args[0], args, create_env_vec(g_env_lst));
		ft_perror("minishell");
    } else if (pid < 0) {
        ft_perror("minishell");
    } else
        wpid = waitpid(pid, &status, WUNTRACED);
	// free(args[0]);
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
