/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:38:26 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/27 19:51:22 by kazumanoda       ###   ########.fr       */
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
	// printf("----execve: %s\n", *args);
    pid = fork();
    if (pid == 0) {
		if (**args != '/')
		{
			tmp = args[0];
			args[0] = get_absolute_path(args[0]);
			free(tmp);
		}
        // 子プロセス
		// printf("----execve: %s\n", *args);
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
        // do {
			// printf("----start: %s\n", *args);
            wpid = waitpid(pid, &status, WUNTRACED);
			// printf("----end: %s\n", *args);
			// printf("status: %d\n", status);
			if (status == 2)
				ft_putstr_fd("\n", 1);
			if (status == 3)
				ft_putstr_fd("^\\Quit: 3\n", 1);
        // } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
	if (status == 256 && args[1])
		return (1);
	if (status == 256)
		return (127);
   	return (status >> 8);
}

int		set_exit_status(int status)
{
	if (status == 0)
		return (ft_export(ft_split("?=0", ' '), &g_env_lst));
	else if (status == 127)
		return (ft_export(ft_split("?=127", ' '), &g_env_lst));
	else
		return (ft_export(ft_split("?=1", ' '), &g_env_lst));
}

int		syntax_check(t_token *token)
{
	if (!ft_strcmp(token->value, ";") || !ft_strcmp(token->value, "|"))
		return (return_with_failure(NULL, NULL, "syntax error", 0));
	while (token->next)
	{
		// printf("%s\n", token->value);
		if (!ft_strcmp(token->value, ";") && token->next->kind != TK_EOF && !ft_strcmp(token->next->value, ";"))
			return (return_with_failure(NULL, NULL, "syntax error", 0));
		if (!ft_strcmp(token->value, "|") && token->next->kind != TK_EOF && !ft_strcmp(token->next->value, "|"))
			return (return_with_failure(NULL, NULL, "syntax error", 0));
		if ((!ft_strcmp(token->value, ">") && token->next->kind != TK_CMD))
			return (return_with_failure(NULL, NULL, "syntax error", 0));
		if ((!ft_strcmp(token->value, "<") && token->next->kind != TK_CMD))
			return (return_with_failure(NULL, NULL, "syntax error", 0));
		token = token->next;
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
			exit(ft_atoi(get_env("?")));
		}
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue;
		}

		if (!syntax_check(validate_token(line)))
		{
			set_env("?", "258");
			free(line);
			continue;
		}
		line = sort_cmd(line);
		fprintf(stderr, "line = %s\n", line);
		job = ft_split(line, ';');
		free(line);

		index = 0;
		while (job[index])
		{
			g_token = tokenize(job[index]);
			t_node *node = command_line();
			// gen(node);
			int		flag[2] = {0, 0};
			// evaluate(node, flag);
			set_exit_status(evaluate(node, flag));
			index++;
		}
		ft_tabfree(job);
	}
}

int		test_sort(char *str)
{
	fprintf(stderr, "before >> %s\n", str);
	str = sort_cmd(str);
	fprintf(stderr, "after >> %s\n", str);
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	t_list	*env_lst;

	(void)argc;
	(void)argv;
	g_env_lst = init_env(envp);
	env_lst = g_env_lst;
	ft_export(ft_split("?=0", ' '), &g_env_lst);
	// disable loop() and turn on test_sort
	// test_sort(ft_strdup(">lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test"));
	loop(&env_lst);
	return (0);
}
