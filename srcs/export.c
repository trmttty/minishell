/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:55:33 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/11 14:38:33 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_declare(void)
{
	t_list	*list;
	char	*name;
	char	*equal;

	sort_env_lst();
	list = g_env_lst;
	while (list)
	{
		if (envcmp(list->content, "_=") != 0
			&& envcmp(list->content, "?=") != 0)
		{
			if ((equal = ft_strchr(list->content, '=')))
			{
				if ((name = ft_substr(list->content, 0,
					equal - (char*)list->content)) == NULL)
					ft_perror("minishell");
				printf("declare -x %s=\"%s\"\n", name, ++equal);
				free(name);
			}
			else
				printf("declare -x %s\n", list->content);
		}
		list = list->next;
	}
	return (1);
}

static int	validate_arg(char *arg)
{
	size_t	i;

	i = 0;
	if (*arg == '=')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (i == 0 && arg[0] >= '0' && arg[0] <= '9')
			return (0);
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'
			|| arg[i] == '+'))
			return (0);
		if (arg[i] == '+' && arg[i + 1] != '=')
			return (0);
		i++;
	}
	return (1);
}

void		update_env(char *arg)
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

void		add_env(char *arg)
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
	t_list	*lst;

	if (*args == NULL)
		return (ft_declare());
	while (*args)
	{
		if (!validate_arg(*args))
			return (error_status("export", *args, "not a valid identifier", 1));
		if ((lst = find_env(*args)) != NULL)
		{
			if (envcmp(lst->content, *args) == '=')
				break ;
			update_env(*args);
		}
		else
			add_env(*args);
		args++;
	}
	return (0);
}
