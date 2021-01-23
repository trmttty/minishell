/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:38:26 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/23 22:37:40 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "signal.h"
#include "knoda.h"

char	*get_absolute_path(char *relative)
{
	char		**paths;
	char		**tmp;
	char		*dir;
	char		*absolute;
	struct stat	sb;

	paths = ft_split(get_env("PATH"), ':');
	tmp = paths;
	while (*paths)
	{
		dir = ft_strjoin(*paths, "/");
		absolute = ft_strjoin(dir, relative);
		free(dir);
		if (stat(absolute , &sb) == 0)
			break;
		free(absolute);
		paths++;
	}
	ft_tabfree(tmp);
	return (absolute);
}

int		launch(char **args) {
    pid_t	pid;
	pid_t	wpid;
    int		status;
	char	*tmp;

    signal(SIGINT, child_sigint);
    pid = fork();
    if (pid == 0) {
		if (**args != '/')
		{
			tmp = args[0];
			args[0] = get_absolute_path(args[0]);
			free(tmp);
		}
        // 子プロセス
        if (execve(args[0], args, (char**)0) == -1) {
			// printf("errno1: %d\n", errno);
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // フォークでエラー
        perror("lsh");
    } else {
        // 親プロセス
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
			// printf("errno2: %d\n", errno);
			// printf("status: %d\n", status);
			if (status == 2)
				ft_putstr_fd("\n", 1);
			if (status == 3)
				ft_putstr_fd("^\\Quit: 3\n", 1);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return (1);
}

void	loop(t_list **env_lst)
{
	char	*line;
	char	**job;
	int		index;
	int		ret;

	while (1)
	{
    	signal(SIGINT, parent_sigint);
    	signal(SIGQUIT, parent_sigquit);
		ft_putstr_fd("> ", 2);
		if ((ret = get_next_line(0, &line)) == 0)
		{
			ft_putstr_fd("exit\n", 2);
			exit(0);
		}
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue;
		}
		job = ft_split(line, ';');
		free(line);

		index = 0;
		while (job[index])
		{
			// tokenize
			g_token = tokenize(job[index]);
			// parser
			t_node *node = command_line();
			// gen(node);
			int		flag[3] = {0, 0, 0};
			evaluate(node, flag);
			index++;
		}
		ft_tabfree(job);
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_list	*env_lst;

	(void)argc;
	(void)argv;
	g_env_lst = init_env(envp);
	env_lst = g_env_lst;
	ft_export(ft_split("?=0", ' '), &g_env_lst);
	loop(&env_lst);
	return (0);
}
