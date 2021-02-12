/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:46:03 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/11 15:15:27 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*init_env_lst(char **envp)
{
	t_list	*env_lst;

	env_lst = NULL;
	while (*envp)
	{
		ft_lstadd_back(&env_lst, ft_lstnew(ft_strdup(*envp)));
		envp++;
	}
	return (env_lst);
}

void		init_env(char *arg)
{
	char	buf[MAXPATHLEN];
	char	*tmp;
	char	*num;
	char	**old_pwd;

	if (getcwd(buf, MAXPATHLEN))
		set_env("PWD", buf);
	tmp = get_env("SHLVL");
	num = ft_itoa(ft_atoi(tmp) + 1);
	set_env("SHLVL", num);
	free(tmp);
	free(num);
	if ((old_pwd = ft_calloc(2, sizeof(char*))) == NULL)
		ft_perror("minishell");
	if ((old_pwd[0] = ft_strdup("OLDPWD")) == NULL)
		ft_perror("minishell");
	ft_export(old_pwd);
	ft_tabfree(old_pwd);
	set_env("_", arg);
	set_question("?", "0");
}

char		*get_env(char *name)
{
	t_list	*tmp;
	char	*value;
	char	*env;

	if ((env = ft_strjoin(name, "=")) == NULL)
		ft_perror("minishell");
	tmp = g_env_lst;
	while (tmp)
	{
		if (envcmp(tmp->content, env) == 0)
		{
			if (ft_strchr(tmp->content, '=') == NULL)
				break ;
			if ((value = ft_strdup(ft_strchr(tmp->content, '=') + 1)) == NULL)
				ft_perror("minishell");
			free(env);
			return (value);
		}
		tmp = tmp->next;
	}
	free(env);
	if ((value = ft_strdup("")) == NULL)
		ft_perror("minishell");
	return (value);
}

int			set_env(char *name, char *value)
{
	char	*tmp;
	char	*env;
	char	**arg;

	if ((tmp = ft_strjoin(name, "=")) == NULL)
		ft_perror("minishell");
	if ((env = ft_strjoin(tmp, value)) == NULL)
		ft_perror("minishell");
	free(tmp);
	if ((arg = ft_calloc(2, sizeof(char*))) == NULL)
		ft_perror("minishell");
	arg[0] = env;
	arg[1] = NULL;
	ft_export(arg);
	free(env);
	free(arg);
	return (0);
}

t_list		*find_env(char *env)
{
	t_list	*tmp;

	tmp = g_env_lst;
	while (tmp)
	{
		if (envcmp(tmp->content, env) == 0
			|| envcmp(tmp->content, env) == '=')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
