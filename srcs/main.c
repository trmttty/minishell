/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:07:07 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/05 11:07:11 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "signal.h"
#include "evaluate.h"
#include "sort_cmd.h"

static void	print_token(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		fprintf(stderr, "token: [%d] [%s]\n", tmp->kind, tmp->value);
		tmp = tmp->next;
	}
}

static int	read_stdin(char **line)
{
	int	ret;

	ft_putstr_fd("> ", 2);
	if ((ret = get_next_line(0, line)) == 0)
	{
		ft_putstr_fd("exit\n", 2);
		exit(ft_atoi(get_env("?")));
	}
	else if (ret == -1)
		ft_perror("minishell");
	if (ft_strlen(*line) == 0 || ft_iswspace_str(*line))
	{
		free(*line);
		return (0);
	}
	if (!check_syntax(*line))
	{
		set_env("?", "258");
		free(*line);
		return (0);
	}
	return (1);
}

static void	execute_minishell(t_lexer *lexer)
{
	int		flag[3];
	t_token	*head;
	t_node	*node;

	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		if ((g_token = generate_token(lexer)) == NULL)
		{
			set_env("_", "");
			continue;
		}
		head = g_token;
		node = command_line();
		flag[0] = 0;
		flag[1] = 0;
		flag[2] = 0;
		set_exit_status(evaluate(node, flag));
		free_node(node);
		free_token(head);
	}
}

static void	loop(void)
{
	char	*line;
	t_lexer *lexer;

	while (1)
	{
		signal(SIGINT, parent_sigint);
		signal(SIGQUIT, parent_sigquit);
		if (!read_stdin(&line))
			continue;
		lexer = new_lexer(line);
		execute_minishell(lexer);
		free(line);
		free(lexer);
	}
}

int			main(int argc, char **argv, char **envp)
{
	(void)argc;
	g_env_lst = init_env_lst(envp);
	init_env(argv[0]);
	loop();
	return (0);
}
