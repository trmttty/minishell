/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 21:05:54 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/15 12:28:59 by ttarumot         ###   ########.fr       */
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

static int	validate_arg(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && arg[0] >= '0' && arg[0] <= '9')
			return (0);
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	validate(char ***args, int *status)
{
	if (!validate_arg(**args))
	{
		*status = 1;
		error_message("unset", **args, "not a valid identifier");
		(*args)++;
		return (0);
	}
	return (1);
}

int			ft_unset(char **args)
{
	t_list	*tmp;
	char	**env;
	int		status;

	status = 0;
	while (*args)
	{
		if (!validate(&args, &status))
			continue;
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
	return (status);
}
