/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   knoda.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:55:18 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/29 01:32:36 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "knoda.h"

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
    signal(SIGINT, SIG_IGN);
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
		else if (wpid < 0)
			perror("minishell");
		else
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			exit(evaluate(node->rnode, flag));
		}
	}
	else if (wpid < 0)
		ft_perror("minishell");
	else
		wait(&status);
	return (status >> 8);
}

int		sample_out_redirect(t_node *node, int *flag)
{
	pid_t	pid;
	int		status;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		if ((fd = open(node->rnode->commands[0], O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
			ft_perror("minishell");
		if (flag[0] == 0)
		{
			dup2(fd, STDOUT_FILENO);
			flag[0] = 1;
		}
		exit(evaluate(node->lnode, flag));
	}
	else if (pid < 0)
		perror("minishell");
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
		if ((fd = open(node->rnode->commands[0], O_WRONLY | O_CREAT | O_APPEND, 0666)) < 0)
			ft_perror("minishell");
		if (flag[0] == 0)
		{
			dup2(fd, STDOUT_FILENO);
			flag[0] = 1;
		}
		exit(evaluate(node->lnode, flag));
	}
	else if (pid < 0)
		perror("minishell");
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
		if ((fd = open (node->rnode->commands[0], O_RDONLY)) < 0)
			ft_perror("minishell");
		if (flag[1] == 0)
		{
			dup2(fd, STDIN_FILENO);
			flag[1] = 1;
		}
		exit(evaluate(node->lnode, flag));
	}
	else if (pid < 0)
		perror("minishell");
	else
		wait(&status);
	return (status >> 8);
}

int		evaluate(t_node *node, int *flag)
{
	if (node->commands != NULL)
		return (sample_exe(node->commands));
	if (ft_strcmp(node->operation, "|") == 0)
		return (sample_pipe(node, flag));
	if (ft_strcmp(node->operation, ">") == 0)
		return (sample_out_redirect(node, flag));
	if (ft_strcmp(node->operation, ">>") == 0)
		return (sample_outout_redirect(node, flag));
	if (ft_strcmp(node->operation, "<") == 0)
		return (sample_in_redirect(node, flag));
	return (0);
}
