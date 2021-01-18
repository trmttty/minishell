/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:46:03 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/18 21:35:54 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*init_env(char **envp)
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

char		*get_env(char *key)
{
	t_list	*tmp;
	char	**env;
	char	*value;
	
	tmp = g_env_lst;
	value = NULL;
	while (tmp)
	{
		env = ft_split((char*)tmp->content, '=');
		if (ft_strcmp(key, env[0]) == 0)
		{
			value = ft_strdup(env[1]);
			break;
		}
		tmp = tmp->next;
	}
	ft_tabfree(env);
	if (value != NULL)
		return (value);
	return (ft_strdup(""));
}