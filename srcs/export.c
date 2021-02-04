/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:55:33 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/04 15:45:19 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_declare(void)
{
	t_list	*list;
	char	**env;

	sort_env_lst();
	list = g_env_lst;
	while (list)
	{
		if (envcmp(list->content, "_=") != 0
			&& envcmp(list->content, "?=") != 0)
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

static int	validate_arg(char *arg)
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

static void	update_env(char *arg)
{
	t_list	*lst;
	char	*plus;
	char	*env;

	if ((lst = find_env(arg)) != NULL)
	{
		if ((plus = ft_strchr(arg, '+')) != NULL)
			env = ft_strjoin(lst->content, &plus[2]);
		else
			env = ft_strdup(arg);
		if (env == NULL)
			ft_perror("minishell");
		free(lst->content);
		lst->content = env;
	}
}

static void	add_env(char *arg)
{
	t_list	*new_lst;
	char	*env;

	if ((env = ft_strdup(arg)) == NULL)
		ft_perror("minishell");
	if ((new_lst = ft_lstnew(env)) == NULL)
		ft_perror("minishell");
	ft_lstadd_back(&g_env_lst, new_lst);
}

int			ft_export(char **args)
{
	if (*args)
	{
		while (*args)
		{
			if (!validate_arg(*args))
			{
				return (error_status("export", *args,
						"not a valid identifier", 0));
			}
			if (find_env(*args))
				update_env(*args);
			else if (!(ft_isalpha(**args) || **args == '_' || **args == '?'))
			{
				return (error_status("export", *args,
						"not a valid identifier", 1));
			}
			else
				add_env(*args);
			args++;
		}
	}
	else
		return (ft_declare());
	return (0);
}
