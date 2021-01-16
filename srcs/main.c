/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:38:26 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/16 23:09:44 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "knoda.h"

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

int		launch_pipe(char **args) {
    pid_t	pid;
	pid_t	wpid;
    int		status;

    pid = fork();
    if (pid == 0) {
	    int		fd2[2];
	    pid_t	pid2;

	    pipe(fd2);
	    if ((pid2 = fork()) == 0) {
	        dup2(fd2[1], 1);
	        close(fd2[0]); close(fd2[1]);
	        execlp(args[0], args[0], (char*)NULL);
	    }
	    dup2(fd2[0], 0);
	    close(fd2[0]);
		close(fd2[1]);
	    execlp(args[2], args[2], (char*)NULL);

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

int		launch_oredirect(char **args) {
    pid_t	pid;
	pid_t	wpid;
    int		status;

    pid = fork();
    if (pid == 0) {
		int	fd;
	    fd = open (args[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	    dup2 (fd, STDOUT_FILENO);
		args[1] = NULL;
	    execvp (args[0], &args[0]);

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

int		launch_iredirect(char **args) {
    pid_t	pid;
	pid_t	wpid;
    int		status;

    pid = fork();
    if (pid == 0) {
		int	fd;
	    fd = open (args[2], O_RDONLY);
	    dup2 (fd, STDIN_FILENO);
		args[1] = NULL;
	    execvp (args[0], &args[0]);

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
	if (ft_tabsize(args) == 3 && ft_strcmp(args[1], "|") == 0)
		return (launch_pipe(args));
	if (ft_tabsize(args) == 3 && ft_strcmp(args[1], ">") == 0)
		return (launch_oredirect(args));
	if (ft_tabsize(args) == 3 && ft_strcmp(args[1], "<") == 0)
		return (launch_iredirect(args));
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

		// lexer
	    lexer_T* lexer = init_lexer(line);
	    token_T* token_l = NULL;
		Token head; head.next = NULL;
		Token *cur = &head;
	    while ((token_l = lexer_get_next_token(lexer)) != NULL)
	    {
			if (token_l->type == TOKEN_ID)
			{
				cur = new_token(TK_CMD, cur, ft_strdup(token_l->value));
      			cur->command = ft_strdup(token_l->value);
			}
			else 
			{
				cur = new_token(TK_RESERVED, cur, ft_strdup(token_l->value));
			}
	        // printf("TOKEN(%d, %s)\n", token->type, token->value);
	    }		
		new_token(TK_EOF, cur, ft_strdup(""));
		token = head.next;

		// parser
		t_node *node = expr();

		// gen(node);
		evaluate(node);
		//

		// args = ft_split(line, ' ');
		// status = execute(args, env_lst);
		free(line);
		// ft_tabfree(args);
		// if (status == 0)
		// 	break;
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
