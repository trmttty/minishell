/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:38:26 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/07 21:47:23 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		launch(char **args) {
    pid_t	pid;
	pid_t	wpid;
    int		status;

    pid = fork();
    if (pid == 0) {
        // 子プロセス
        if (execvp(args[0], args) == -1) {
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
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    
    return (1);
}

int		execute(char **args, t_list **env_lst)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(&args[1], env_lst));
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(&args[1], env_lst));
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(&args[1], env_lst));
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(&args[1], env_lst));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(&args[1], env_lst));
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(&args[1], env_lst));
	if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(&args[1], env_lst));
	return launch(args);
}

void	loop(t_list **env_lst)
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
		status = execute(args, env_lst);
		free(line);
		ft_tabfree(args);
		if (status == 0)
			break;
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_list	*env_lst;

	(void)argc;
	(void)argv;
	env_lst = init_env(envp);
	loop(&env_lst);
	return (0);
}
