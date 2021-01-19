/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:38:26 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/19 18:29:31 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "knoda.h"

char	*get_absolute_path(char *relative)
{
	char		**paths;
	char		**tmp;
	char		*dir;
	char		*target;
	struct stat	sb;
	

	paths = ft_split(get_env("PATH"), ':');
	tmp = paths;
	while (*paths)
	{
		dir = ft_strjoin(*paths, "/");
		target = ft_strjoin(dir, relative);
		free(dir);
		if (stat(target, &sb) == 0)
			break;
		free(target);
		paths++;
	}
	ft_tabfree(tmp);
	return (target);
}

int		launch(char **args) {
    pid_t	pid;
	pid_t	wpid;
    int		status;
	char	*tmp;

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

// int		launch_pipe(char **args) {
//     pid_t	pid;
// 	pid_t	wpid;
//     int		status;

//     pid = fork();
//     if (pid == 0) {
// 	    int		fd2[2];
// 	    pid_t	pid2;

// 	    pipe(fd2);
// 	    if ((pid2 = fork()) == 0) {
// 	        dup2(fd2[1], 1);
// 	        close(fd2[0]); close(fd2[1]);
// 	        execlp(args[0], args[0], (char*)NULL);
// 	    }
// 	    dup2(fd2[0], 0);
// 	    close(fd2[0]);
// 		close(fd2[1]);
// 	    execlp(args[2], args[2], (char*)NULL);

//     } else if (pid < 0) {
//         // フォークでエラー
//         perror("lsh");
//     } else {
//         // 親プロセス
//         do {
//             wpid = waitpid(pid, &status, WUNTRACED);
//         } while (!WIFEXITED(status) && !WIFSIGNALED(status));
//     }

//     return (1);
// }

// int		launch_oredirect(char **args) {
//     pid_t	pid;
// 	pid_t	wpid;
//     int		status;

//     pid = fork();
//     if (pid == 0) {
// 		int	fd;
// 	    fd = open (args[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 	    dup2 (fd, STDOUT_FILENO);
// 		args[1] = NULL;
// 	    execvp (args[0], &args[0]);

//     } else if (pid < 0) {
//         // フォークでエラー
//         perror("lsh");
//     } else {
//         // 親プロセス
//         do {
//             wpid = waitpid(pid, &status, WUNTRACED);
//         } while (!WIFEXITED(status) && !WIFSIGNALED(status));
//     }

//     return (1);
// }

// int		launch_iredirect(char **args) {
//     pid_t	pid;
// 	pid_t	wpid;
//     int		status;

//     pid = fork();
//     if (pid == 0) {
// 		int	fd;
// 	    fd = open (args[2], O_RDONLY);
// 	    dup2 (fd, STDIN_FILENO);
// 		args[1] = NULL;
// 	    execvp (args[0], &args[0]);

//     } else if (pid < 0) {
//         // フォークでエラー
//         perror("lsh");
//     } else {
//         // 親プロセス
//         do {
//             wpid = waitpid(pid, &status, WUNTRACED);
//         } while (!WIFEXITED(status) && !WIFSIGNALED(status));
//     }

//     return (1);
// }


// int		execute(char **args, t_list **env_lst)
// {
// 	if (ft_tabsize(args) == 3 && ft_strcmp(args[1], "|") == 0)
// 		return (launch_pipe(args));
// 	if (ft_tabsize(args) == 3 && ft_strcmp(args[1], ">") == 0)
// 		return (launch_oredirect(args));
// 	if (ft_tabsize(args) == 3 && ft_strcmp(args[1], "<") == 0)
// 		return (launch_iredirect(args));
// 	if (ft_strcmp(args[0], "echo") == 0)
// 		return (ft_echo(&args[1], env_lst));
// 	if (ft_strcmp(args[0], "cd") == 0)
// 		return (ft_cd(&args[1], env_lst));
// 	if (ft_strcmp(args[0], "export") == 0)
// 		return (ft_export(&args[1], env_lst));
// 	if (ft_strcmp(args[0], "unset") == 0)
// 		return (ft_unset(&args[1], env_lst));
// 	if (ft_strcmp(args[0], "pwd") == 0)
// 		return (ft_pwd(&args[1], env_lst));
// 	if (ft_strcmp(args[0], "env") == 0)
// 		return (ft_env(&args[1], env_lst));
// 	if (ft_strcmp(args[0], "exit") == 0)
// 		return (ft_exit(&args[1], env_lst));
// 	return launch(args);
// }

void	loop(t_list **env_lst)
{
	char	*line;
	char	**job;
	int		index;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		get_next_line(0, &line);
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
	loop(&env_lst);
	return (0);
}
