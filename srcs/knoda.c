/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   knoda.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:55:18 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/18 15:43:17 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "knoda.h"

// t_node	*new_node(char **cmd, char *op, t_node *left, t_node *right)
// {
// 	t_node	*node;

// 	node = (t_node *)ft_calloc(1, sizeof(t_node));
// 	node->command = cmd;
// 	node->operation = op;
// 	node->lnode = left;
// 	node->rnode = right;
// 	return (node);
// }

int		sample_exe(char **args)
{
	t_list		**env_lst;

	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(&args[1], env_lst));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(&args[1], env_lst));
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(&args[1], env_lst));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(&args[1], env_lst));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(&args[1], env_lst));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(&args[1], env_lst));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(&args[1], env_lst));
	return launch(args);
}

int		sample_pipe(t_node *node)
{
	int		fd[2];
	int		status;
	pid_t	pid;
	pid_t	wpid;
	pid_t	super_pid;

	if ((wpid = fork()) == 0)
	{
		pipe(fd);
		if ((pid = fork()) == 0)
		{
			// fprintf(stderr, "		child_in pid>%d, wpid>%d\n", pid, wpid);
			dup2(fd[1], 1);
			close (fd[0]);
			close (fd[1]);
			evaluate(node->lnode);
			// fprintf(stderr, "		child_out pid>%d, wpid>%d\n", pid, wpid);
			exit(2);
		}
		// fprintf(stderr, "	parent_in pid>%d, wpid>%d\n", pid, wpid);
		wait(NULL);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		evaluate(node->rnode);
		// fprintf(stderr, "	parent_out pid>%d, wpid>%d\n", pid, wpid);
		exit(2);
	}
	else if (wpid < 0)
		perror("lsh");
	else
	{
		// fprintf(stderr, "supervisor_in pid>%d, wpid>%d\n", pid, wpid);
		wait(NULL);
		// do
		// {
		// 	super_pid = waitpid(wpid, &status, WUNTRACED);
		// } while (!WIFEXITED(status) && !WIFSIGNALED(status));
		// fprintf(stderr, "supervisor_out pid>%d, wpid>%d\n", pid, wpid);
	}
	return (1);
}

int		sample_out_redirect(t_node *node)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open(node->rnode->commands[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		dup2(fd, STDOUT_FILENO);
		evaluate(node->lnode);
		exit(2);
	}
	else if (pid < 0)
		perror("lsh");
	else
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

int		sample_in_redirect(t_node *node)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open (node->rnode->commands[0], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		evaluate(node->lnode);
		exit(2);
	}
	else if (pid < 0)
		perror("lsh");
	else
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}


int		evaluate(t_node *node)
{
	if (node->commands != NULL)
	{
		// fprintf(stderr, "exe > %s\n", node->command[0]);
		return (sample_exe(node->commands));
	}
	if (ft_strcmp(node->operation, "|") == 0)
	{
		//子プロセス立ち上げ、配管工事（標準出力と標準入力を繋げる）
		return (sample_pipe(node));
	}
	if (ft_strcmp(node->operation, ">") == 0)
	{
		return (sample_out_redirect(node));
	}
	if (ft_strcmp(node->operation, "<") == 0)
	{
		return (sample_in_redirect(node));
	}
	return (0);
}

// int		test_main()
// {
// 	t_node	*echo_node = new_node(ft_split("echo cba", ' '), NULL, NULL, NULL);
// 	t_node	*cat_node = new_node(ft_split("cat", ' '), NULL, NULL, NULL);
// 	t_node	*ls_node = new_node(ft_split("ls", ' '), NULL, NULL, NULL);
// 	t_node	*wc_node = new_node(ft_split("wc", ' '), NULL, NULL, NULL);
// 	t_node	*test_node = new_node(ft_split("test.txt", ' '), NULL, NULL, NULL);

// 	// ls | wc | cat
// 	t_node	*pipe_node = new_node(NULL, ft_strdup("|"), echo_node, cat_node);
// 	t_node	*pipe_node2 = new_node(NULL, ft_strdup("|"), pipe_node, cat_node);

// 	t_node	*out_redirect_node = new_node(NULL, ft_strdup(">"), echo_node, test_node);
// 	t_node	*in_redirect_node = new_node(NULL, ft_strdup("<"), wc_node, test_node);

// 	evaluate(pipe_node2);
// 	return (0);
// }