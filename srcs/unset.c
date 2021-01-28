/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 21:05:54 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/29 01:54:13 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unset(char **args, t_list **env_lst)
{
	t_list	*del;
	t_list	*tmp;
	char	**env;

	if (*args == NULL)
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		return (1);
	}
	while (*args)
	{
		tmp = g_env_lst;
		env = ft_split((char*)tmp->content, '=');
		if (ft_strcmp(*args, env[0]) == 0)
		{
			// *env_lst = tmp->next;
			g_env_lst = tmp->next;
			ft_lstdelone(tmp, free);
		}

		while (tmp->next)
		{
			ft_tabfree(env);
			env = ft_split((char*)tmp->next->content, '=');
			if (ft_strcmp(*args, env[0]) == 0)
			{
				del = tmp->next;
				tmp->next = tmp->next->next;
				ft_lstdelone(del, free);
			}
			tmp = tmp->next;
		}
		ft_tabfree(env);
		args++;
	}
	return (1);
}

