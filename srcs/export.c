/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:55:33 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/23 01:16:46 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		envcmp(const char *env1, const char *env2)
{
	while (*env1 && *env1 != '=' && *env1 == *env2)
	{
		env1++;
		env2++;
	}
	return (*env1 - *env2);
}

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

int		ft_export(char **args, t_list **env_lst)
{
	t_list	*lst;
	char	*env;

	if (*args)
	{
		while (*args)
		{
			if ((lst = find_env(&g_env_lst, *args)) != NULL)
			{
				free(lst->content);
				lst->content = ft_strdup(*args);
			}
			else
			{
				if (!(ft_isalpha(**args) || **args == '_' || **args == '?'))
				{
					return (return_with_failure("export", *args, "not a valid identifier", 0));
				}
				env = ft_strdup(*args);
				ft_lstadd_back(&g_env_lst, ft_lstnew(env));
			}
			args++;
		}
	}
	else
		return (ft_declare(env_lst));
	return (1);
}
