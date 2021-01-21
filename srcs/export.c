/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:55:33 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/21 18:59:14 by kazumanoda       ###   ########.fr       */
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
		if (envcmp((char*)tmp->content, env) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
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
				if (ft_isdigit(**args))
				{
					fprintf(stderr, "lsh: export: `%s': not a valid identifier\n", *args);
					return (0);
				}
				env = ft_strdup(*args);
				ft_lstadd_back(&g_env_lst, ft_lstnew(env));
			}
			args++;
		}
	}
	return (1);
}
