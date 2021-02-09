/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:19:56 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/02/09 11:34:05 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "evaluate.h"

// void	child_pipe(t_node *node, int *flag)
// {
// 	int		fd[2];
// 	pid_t	pid;

// 	if (pipe(fd) == -1)
// 		ft_perror("minishell");
// 	if ((pid = fork()) == 0)
// 	{
// 		dup2(fd[1], 1);
// 		close(fd[0]);
// 		close(fd[1]);
// 		exit(evaluate(node->lnode, flag));
// 	}
// 	else if (pid < 0)
// 		ft_perror("minishell");
// 	else
// 	{
// 		dup2(fd[0], 0);
// 		close(fd[0]);
// 		close(fd[1]);
// 		exit(evaluate(node->rnode, flag));
// 	}
// }

// int		ft_pipe(t_node *node, int *flag)
// {
// 	int		status;
// 	pid_t	wpid;

// 	set_env("_", "");
// 	flag[0] = 0;
// 	flag[1] = 0;
// 	status = 0;
// 	if ((wpid = fork()) == 0)
// 		child_pipe(node, flag);
// 	else if (wpid < 0)
// 		ft_perror("minishell");
// 	else
// 		wait(&status);
// 	return (status >> 8);
// }

// #include "minishell.h"
// #include "evaluate.h"

// void	child_pipe(t_node *node, int *flag)
// {
// 	int		fd[2];
// 	pid_t	pid;
// 	// pid_t	pid1;

// 	if (pipe(fd) == -1)
// 		ft_perror("minishell");
// 	if ((pid = fork()) == 0)
// 	{
// 		dup2(fd[0], 0);
// 		close(fd[0]);
// 		close(fd[1]);
// 		exit(evaluate(node->rnode, flag));
// 	}
// 	else if (pid < 0)
// 		ft_perror("minishell");
// 	else
// 	{
// 			dup2(fd[1], 1);
// 			close(fd[0]);
// 			close(fd[1]);
// 			evaluate(node->lnode, flag);
// 	}
// }

int		ft_pipe(t_node *node, int *flag)
{
	int		status;
	pid_t	wpid;
	pid_t	pid;

	// set_env("_", "");
	// flag[0] = 0;
	// flag[1] = 0;
	// status = 0;
	// // if ((wpid = fork()) == 0)
	// 	child_pipe(node, flag);
	// // else if (wpid < 0)
	// // 	ft_perror("minishell");
	// // else
	// // 	wait(&status);
	// return (status >> 8);
	/* ls | wc の実行 */
	int fildes[2];
	pipe(fildes);
	if ((pid = fork()) == 0) {        /* 出力側子プロセス */
	    dup2(fildes[1], 1);
	    close(fildes[0]);
	    close(fildes[1]);
	    exit(evaluate(node->lnode, flag));
	}
	else
	{
	    if ((wpid = fork()) == 0) {    /* 入力側プロセス */
	        dup2(fildes[0], 0);
	        close(fildes[0]);
	        close(fildes[1]);
	        exit(evaluate(node->rnode, flag));
	    }
	    else {             /* 親プロセス */
	        close(fildes[0]);
	        close(fildes[1]);
			waitpid(wpid, &status, WUNTRACED);
			waitpid(pid, NULL, WUNTRACED);
	    }
	}
	// printf("%d status\n", status);
	return (status >> 8);
}


// /* ls | wc の実行 */
// int fildes[2];
// pipe(fildes);
// if (fork() == 0) {        /* 出力側子プロセス */
//     dup2(fildes[1], 1);
//     close(fildes[0]);
//     close(fildes[1]);
//     execl("/bin/ls", ...);
// }
// else
//     if (fork() == 0) {    /* 入力側プロセス */
//         dup2(fildes[0], 0);
//         close(fildes[0]);
//         close(fildes[1]);
//         execl("/bin/wc", ...);
//     }
//     else {                /* 親プロセス */
//         close(fildes[0]);
//         close(fildes[1]);
//         wait();
//         wait();
//     }