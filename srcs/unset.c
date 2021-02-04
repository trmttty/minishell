/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 21:05:54 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/04 15:49:15 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env(char *name)
{
	t_list	*del;
	t_list	*tmp;
	char	**env;

	tmp = g_env_lst;
	while (tmp->next)
	{
		if ((env = ft_split(tmp->next->content, '=')) == NULL)
			ft_perror("minishell");
		if (env[0] && ft_strcmp(name, env[0]) == 0)
		{
			del = tmp->next;
			tmp->next = tmp->next->next;
			ft_lstdelone(del, free);
			ft_tabfree(env);
			return ;
		}
		ft_tabfree(env);
		tmp = tmp->next;
	}
}

int			ft_unset(char **args)
{
	t_list	*tmp;
	char	**env;

	while (*args)
	{
		tmp = g_env_lst;
		if ((env = ft_split(tmp->content, '=')) == NULL)
			ft_perror("minishell");
		if (env[0] && ft_strcmp(*args, env[0]) == 0)
		{
			g_env_lst = tmp->next;
			ft_lstdelone(tmp, free);
			ft_tabfree(env);
			args++;
			continue;
		}
		ft_tabfree(env);
		remove_env(*args);
		args++;
	}
	return (1);
}
