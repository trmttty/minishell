/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:55:33 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/31 23:24:10 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*find_env(t_list **env_lst, char *env)
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

void	sort_env_lst(t_list *env_lst)
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

int		ft_declare(t_list **env_lst)
{
	t_list	*list;
	char	**env;

	sort_env_lst(g_env_lst);
	list = g_env_lst;
	while (list)
	{
		if (envcmp(list->content, "_=") != 0 &&
			envcmp(list->content, "?=") != 0)
		{
			env = ft_split(list->content, '=');
			if (env[1] != NULL)
				printf("declare -x %s=\"%s\"\n", env[0], env[1]);
			else
				printf("declare -x %s\n", env[0]);
			ft_tabfree(env);
		}
		list = list->next;
	}
	return (1);
}

int		validate_arg(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (i == 0 && arg[0] >= '0' && arg[0] <= '9')
			return (0);
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'
				|| arg[i] == '?' || arg[i] == '+'))
			return (0);
		if (arg[i] == '+' && arg[i + 1] != '=')
			return (0);
		i++;
	}
	return (1);
}

int		ft_export(char **args, t_list **env_lst)
{
	t_list	*lst;
	t_list	*new_lst;
	char	*env;
	char	*plus;

	if (*args)
	{
		while (*args)
		{
			if (!validate_arg(*args))
			{
				return (return_failure("export", *args,
						"not a valid identifier", 0));
			}
			if ((lst = find_env(&g_env_lst, *args)) != NULL)
			{
				if ((plus = ft_strchr(*args, '+')) != NULL)
					env = ft_strjoin(lst->content, &plus[2]);
				else
					env = ft_strdup(*args);
				if (env == NULL)
					ft_perror("minishell");
				free(lst->content);
				lst->content = env;
			}
			else
			{
				if (!(ft_isalpha(**args) || **args == '_' || **args == '?'))
				{
					return (return_failure("export", *args,
							"not a valid identifier", 1));
				}
				if ((env = ft_strdup(*args)) == NULL)
					ft_perror("minishell");
				if ((new_lst = ft_lstnew(env)) == NULL)
					ft_perror("minishell");
				ft_lstadd_back(&g_env_lst, new_lst);
			}
			args++;
		}
	}
	else
		return (ft_declare(env_lst));
	return (0);
}
