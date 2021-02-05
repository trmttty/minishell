/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:46:03 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/05 10:10:28 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*generate_env_lst(char **envp)
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

	if (getcwd(buf, MAXPATHLEN))
		set_env("PWD", buf);
	tmp = get_env("SHLVL");
	num = ft_itoa(ft_atoi(tmp) + 1);
	set_env("SHLVL", num);
	free(tmp);
	free(num);
	set_env("_", arg);
	set_env("?", "0");
}

int		envcmp(const char *env1, const char *env2)
{
	while (*env1 && *env1 != '=' && *env1 == *env2)
	{
		env1++;
		env2++;
	}
	if (*env2 == '+')
		env2++;
	return (*env1 - *env2);
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
	if ((arg = ft_split(env, ' ')) == NULL)
		ft_perror("minishell");
	ft_export(arg);
	free(env);
	ft_tabfree(arg);
	return (0);
}

t_list	*find_env(char *env)
{
	t_list	*tmp;

	tmp = g_env_lst;
	while (tmp)
	{
		if (envcmp(tmp->content, env) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	sort_env_lst()
{
	t_list	*list;
	void	*content;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		list = g_env_lst;
		while (list->next)
		{
			if (envcmp(list->content, list->next->content) > 0)
			{
				content = list->content;
				list->content = list->next->content;
				list->next->content = content;
				swapped = 1;
			}
			list = list->next;
		}
	}
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
