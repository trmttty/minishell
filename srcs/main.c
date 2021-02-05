/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:38:26 by ttarumot          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/02/05 09:13:12 by ttarumot         ###   ########.fr       */
=======
/*   Updated: 2021/02/05 10:21:33 by ttarumot         ###   ########.fr       */
>>>>>>> trmt-dev
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "signal.h"
#include "evaluate.h"
#include "sort_cmd.h"

void	print_token(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		fprintf(stderr, "token: [%d] [%s]\n", tmp->kind, tmp->value);
		tmp = tmp->next;
	}
}

void	loop(void)
{
	char	*line;
	int		ret;
	int		flag[3];
	t_token	*head;
	t_node	*node;
	t_lexer *lexer;

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
		else if (ret == -1)
			ft_perror("minishell");
		if (ft_strlen(line) == 0 || ft_iswspace_str(line))
		{
			free(line);
			continue;
		}
		if (!check_syntax(line))
		{
			set_env("?", "258");
			free(line);
			continue;
		}
		// fprintf(stderr, "before: [%s]\n", line);
		// line = sort_cmd(line);
		// fprintf(stderr, "after: [%s]\n", line);
		lexer = init_lexer(line);
		while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
		{
			if ((g_token = generate_token(lexer)) == NULL)
			{
				set_env("_", "");
                continue;
			}
			head = g_token;
			sort_token();
			node = command_line();
			// gen(node);
			// print_token(head);
			flag[0] = 0;
			flag[1] = 0;
			flag[2] = 0;
			set_exit_status(evaluate(node, flag));
			free_node(node);
			free_token(head);
		}
		free(line);
		free(lexer);
	}
}

int		main(int argc, char **argv, char **envp)
{
	(void)argc;
	g_env_lst = generate_env_lst(envp);
	init_env(argv[0]);
	loop();
	return (0);
}
