/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:38:26 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/03 23:14:40 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "signal.h"
#include "evaluate.h"
#include "sort_cmd.h"

char	*get_absolute_path(char *relative)
{
	char		**paths;
	char		**tmp;
	char		*dir;
	char		*env;
	char		*absolute;
	struct stat	sb;

	env = get_env("PATH");
	if ((paths = ft_split(env, ':')) == NULL)
		ft_perror("minishell");
	free(env);
	tmp = paths;
	if ((absolute = ft_strdup("")) == NULL)
		ft_perror("minishell");
	while (*paths)
	{
		if ((dir = ft_strjoin(*paths, "/")) == NULL)
			ft_perror("minishell");
		free(absolute);
		if ((absolute = ft_strjoin(dir, relative)) == NULL)
			ft_perror("minishell");
		free(dir);
		if (stat(absolute , &sb) == 0)
			break;
		paths++;
	}
	ft_tabfree(tmp);
	return (absolute);
}

char	**create_env_vec(t_list *env_lst)
{
	char	**env_vec;
	int		size;
	int		i;

	size = ft_lstsize(env_lst);
	if ((env_vec = ft_calloc(size + 1, sizeof(char*))) == NULL)
        ft_perror("minishell");
	i = 0;
	while (i < size)
	{
		if ((env_vec[i] = ft_strdup(env_lst->content)) == NULL)
			ft_perror("minishell");
		i++;
		env_lst = env_lst->next;
	}
	env_vec[i] = NULL;
	return (env_vec);
}

int		launch(char **args) {
    pid_t	pid;
	pid_t	wpid;
    int		status;
	char	*tmp;

    signal(SIGINT, child_sigint);
	pid = 0;
	status = 0;
	if (**args != '/')
	{
		tmp = args[0];
		if ((args[0] = get_absolute_path(args[0])) != NULL)
			set_env("_", args[0]);
		free(tmp);
	}
    if ((pid = fork()) == 0)
	{
        execve(args[0], args, create_env_vec(g_env_lst));
		ft_perror("minishell");
    } else if (pid < 0) {
        ft_perror("minishell");
    } else
        wpid = waitpid(pid, &status, WUNTRACED);
	// free(args[0]);
	if (status == 2)
		ft_putstr_fd("\n", 1);
	if (status == 3)
		ft_putstr_fd("^\\Quit: 3\n", 1);
	if (status == 256 && args[1])
		return (1);
	if (status == 256)
		return (127);
   	return (status >> 8);
}

int		set_exit_status(int status)
{
	if (status == 0)
		return (set_env("?", "0"));
	else if (status == 127)
		return (set_env("?", "127"));
	else
		return (set_env("?", "1"));
}

int		syntax_check(t_token *token)
{
	if (!ft_strcmp(token->value, ";") || !ft_strcmp(token->value, "|"))
		return (0);
	while (token->next)
	{
		if ((!ft_strcmp(token->value, ";") || !ft_strcmp(token->value, "|"))
			&& token->next->kind != TK_EOF
			&& ((!ft_strcmp(token->next->value, ";") || !ft_strcmp(token->next->value, "|"))))
			return (0);
		if ((!ft_strcmp(token->value, ">") || !ft_strcmp(token->value, ">>") || !ft_strcmp(token->value, "<"))
			&& token->next->kind == TK_RESERVED)
			return (0);
		if ((!ft_strcmp(token->value, ">") && token->next->kind == TK_EOF))
			return (0);
		if ((!ft_strcmp(token->value, ">>") && token->next->kind == TK_EOF))
			return (0);
		if ((!ft_strcmp(token->value, "<") && token->next->kind == TK_EOF))
			return (0);
		if ((!ft_strcmp(token->value, "|") && token->next->kind == TK_EOF))
			return (0);
		token = token->next;
	}
	return (1);
}

t_token*    lexer_get_next_checker(t_lexer* lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == ' ' || lexer->c == '\n')
			lexer_skip_whitespace(lexer);
		if (lexer->pc == ' ' && (lexer->c == '"' || lexer->c == '\''))
			return (lexer_collect_string(lexer, lexer->c));
		if (ft_strchr(";<>|", lexer->c))
			return (lexer_advance_with_token(lexer, init_token(TK_RESERVED, lexer_get_current_char_as_string(lexer))));
		return (lexer_collect_string(lexer, 0));
	}
	return (NULL);
}

t_token		*generate_checker(t_lexer *lexer)
{
	t_token		*token;
	t_token		token_head;
	t_token		*cur;

	token_head.next = NULL;
	cur = &token_head;
	while ((token = lexer_get_next_checker(lexer)) != NULL)
	{
		cur = new_token(token->kind, cur, token->value);
		free(token->value);
		free(token);
	}
	if (token_head.next)
		new_token(TK_EOF, cur, NULL);
	return(token_head.next);
}


int		check_syntax(char *line)
{
	t_token *token;
	t_lexer	*lexer;
	int		ret;

	if (in_bracket(line, ft_strlen(line) - 1))
		return (return_failure(NULL, NULL, "syntax error", 0));
	lexer = init_lexer(line);
	ret = 0;
	if ((token = generate_checker(lexer)) != NULL)
	{
		ret = syntax_check(token);
		free_token1(token);
	}
	free(lexer);
	if (ret)
		return (1);
	return (return_failure(NULL, NULL, "syntax error", 0));
}

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

void	loop(t_list **env_lst)
{
	char	*line;
	int		ret;
	int		flag[3];
	t_token	*head;
	t_node	*node;
	t_lexer *lexer;

	(void)env_lst;
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
		if (ft_strlen(line) == 0)
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
		// fprintf(stderr, "%s\n", line);
		line = sort_cmd(line);
		// fprintf(stderr, "%s\n", line);
		lexer = init_lexer(line);
		while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
		{
			if ((g_token = generate_token(lexer)) == NULL)
			{
				set_env("_", "");
                continue;
			}
			head = g_token;
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

void	set_environment(char *arg)
{
	char	buf[MAXPATHLEN];
	char	*tmp;
	char	*num;
	// char	*path;

	if (getcwd(buf, MAXPATHLEN))
		set_env("PWD", buf);
	tmp = get_env("SHLVL");
	num = ft_itoa(ft_atoi(tmp) + 1);
	set_env("SHLVL", num);
	free(tmp);
	free(num);
	set_env("_", arg);
	// free(path);
	set_env("?", "0");
}

int		main(int argc, char **argv, char **envp)
{
	t_list	*env_lst;

	(void)argc;
	g_env_lst = init_env(envp);
	env_lst = g_env_lst;
	set_environment(argv[0]);
	loop(&env_lst);
	return (0);
}
