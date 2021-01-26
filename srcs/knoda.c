/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   knoda.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:55:18 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/26 18:43:52 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "knoda.h"

// t_node	*new_node(char **cmd, char *op, t_node *left, t_node *right)
// {
// 	t_node	*node;

// 	node = (t_node *)ft_calloc(1, sizeof(t_node));
// 	node->commands = cmd;
// 	node->operation = op;
// 	node->lnode = left;
// 	node->rnode = right;
// 	return (node);
// }

int		sample_exe(char **args)
{
	t_list		**env_lst;

	if (args[0] != NULL)
	{
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
	}
	return launch(args);
}

int		sample_pipe(t_node *node, int *flag)
{
	int		fd[2];
	int		status;
	pid_t	pid;
	pid_t	wpid;

	flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;
	if ((wpid = fork()) == 0)
	{
		pipe(fd);
		if ((pid = fork()) == 0)
		{
			dup2(fd[1], 1);
			close (fd[0]);
			close (fd[1]);
			exit(evaluate(node->lnode, flag));
		}
		// printf("----pipe start: %s\n", node->operation);
		// wait(NULL);
        // wpid = waitpid(pid, &status, WUNTRACED);
		// printf("----pipe end: %s\n", node->operation);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		exit(evaluate(node->rnode, flag));
		// evaluate(node->rnode, flag);
	}
	else if (wpid < 0)
		perror("lsh");
	else
	{
		wait(&status);
		// fprintf(stderr, "pipe > %d\n", status);
	}
	return (status >> 8);
}

int		sample_colon(t_node *node, int *flag)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	if ((wpid = fork()) == 0)
	{
		if ((pid = fork()) == 0)
		{
			exit(evaluate(node->lnode, flag));
		}
		wait(NULL);
		exit(evaluate(node->rnode, flag));
	}
	else if (wpid < 0)
		perror("lsh");
	else
		wait(&status);
	return (status);
}

int		sample_out_redirect(t_node *node, int *flag)
{
	pid_t	pid;
	int		status;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open(node->rnode->commands[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (flag[0] == 0)
		{
			dup2(fd, STDOUT_FILENO);
			flag[0] = 1;
		}
		exit(evaluate(node->lnode, flag));
	}
	else if (pid < 0)
		perror("lsh");
	else
		wait(&status);
	return (status >> 8);
}

int		sample_outout_redirect(t_node *node, int *flag)
{
	pid_t	pid;
	int		status;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open(node->rnode->commands[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (flag[2] == 0)
		{
			dup2(fd, STDOUT_FILENO);
			flag[2] = 1;
		}
		exit(evaluate(node->lnode, flag));
	}
	else if (pid < 0)
		perror("lsh");
	else
		wait(&status);
	return (status >> 8);
}

int		sample_in_redirect(t_node *node, int *flag)
{
	pid_t	pid;
	int		status;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open (node->rnode->commands[0], O_RDONLY);
		if (flag[1] == 0)
		{
			dup2(fd, STDIN_FILENO);
			flag[1] = 1;
		}
		exit(evaluate(node->lnode, flag));
	}
	else if (pid < 0)
		perror("lsh");
	else
		wait(&status);
	return (status >> 8);
}

// int		set_exit_status(int status)
// {
// 	if (status == 0)
// 		return (ft_export(ft_split("?=0", ' '), &g_env_lst));
// 	else if (status == 256)
// 		return (ft_export(ft_split("?=127", ' '), &g_env_lst));
// 	else
// 		return (ft_export(ft_split("?=1", ' '), &g_env_lst));
// }

int		evaluate(t_node *node, int *flag)
{
	if (node->commands != NULL)
	{
		// return (set_exit_status(sample_exe(node->commands)));
		return (sample_exe(node->commands));
	}
	if (ft_strcmp(node->operation, "|") == 0)
		return (sample_pipe(node, flag));
	if (ft_strcmp(node->operation, ";") == 0)
		return (sample_colon(node, flag));
	if (ft_strcmp(node->operation, ">") == 0)
		return (sample_out_redirect(node, flag));
	if (ft_strcmp(node->operation, ">>") == 0)
		return (sample_outout_redirect(node, flag));
	if (ft_strcmp(node->operation, "<") == 0)
		return (sample_in_redirect(node, flag));
	return (0);
}
// int		test_main()
// {
// 	t_node	*echo1_node = n_node(ft_split("echo 1", ' '), NULL, NULL, NULL);
// 	t_node	*echo2_node = n_node(ft_split("echo 2", ' '), NULL, NULL, NULL);
// 	t_node	*cat_node = n_node(ft_split("cat", ' '), NULL, NULL, NULL);
// 	t_node	*ls_node = n_node(ft_split("ls", ' '), NULL, NULL, NULL);
// 	t_node	*wc_node = n_node(ft_split("wc", ' '), NULL, NULL, NULL);
// 	t_node	*test_node = n_node(ft_split("test.txt", ' '), NULL, NULL, NULL);
// 	t_node	*in1_node = n_node(ft_split("in1", ' '), NULL, NULL, NULL);
// 	t_node	*in2_node = n_node(ft_split("in2", ' '), NULL, NULL, NULL);
// 	t_node	*out1_node = n_node(ft_split("out1", ' '), NULL, NULL, NULL);
// 	t_node	*out2_node = n_node(ft_split("out2", ' '), NULL, NULL, NULL);

// 	// ls | wc | cat

// 	t_node	*cat_out_node1 = n_node(NULL, ft_strdup(">"), cat_node, out1_node);
// 	t_node	*cat_out_node2 = n_node(NULL, ft_strdup(">"), cat_out_node1, out2_node);
// 	t_node	*cat_in_node1 = n_node(NULL, ft_strdup("<"), cat_out_node2, in1_node);
// 	t_node	*cat_in_node2 = n_node(NULL, ft_strdup("<"), cat_in_node1, in2_node);

// 	t_node	*echo_in_node2 = n_node(NULL, ft_strdup(">"), echo2_node, in2_node);

// 	t_node	*colon_node = n_node(NULL, ft_strdup(";"), echo_in_node2, cat_in_node2);

// 	t_node	*echo_in_node1 = n_node(NULL, ft_strdup(">"), echo1_node, in1_node);

// 	t_node	*colon_node2 = n_node(NULL, ft_strdup(";"), echo_in_node1, colon_node);



// 	t_node	*echo_abc_node = n_node(ft_split("echo abc", ' '), NULL, NULL, NULL);
// 	t_node	*echo_out_node1 = n_node(NULL, ft_strdup(">"), echo_abc_node, out1_node);
// 	t_node	*echo_out_node2 = n_node(NULL, ft_strdup(">"), echo_out_node1, out2_node);

// 	int		flag[3] = {0, 0, 0};
// 	// 0 >, 1 <, 2 >>
// 	evaluate(echo_out_node2, flag);
// 	return (0);
// }
