/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:55:33 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/15 11:43:54 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_arg(char *arg)
{
	size_t	i;

	i = 0;
	if (*arg == '=' || *arg == '+')
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

static int	validate(char ***args, int *status)
{
	if (!validate_arg(**args))
	{
		*status = 1;
		error_message("export", **args, "not a valid identifier");
		(*args)++;
		return (0);
	}
	return (1);
}

void		update_env(char *arg)
{
	t_list	*lst;
	char	*equal;
	char	*env;

	if ((lst = find_env(arg)) != NULL)
	{
		if ((equal = ft_strchr(arg, '=')) && *(equal - 1) == '+')
		{
			if ((ft_strchr(lst->content, '=')))
				env = ft_strjoin(lst->content, equal + 1);
			else
			{
				*(equal - 1) = '\0';
				env = ft_strjoin(arg, equal);
			}
		}
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
	char	*equal;

	if ((equal = ft_strchr(arg, '=')) && *(equal - 1) == '+')
	{
		*(equal - 1) = '\0';
		if ((env = ft_strjoin(arg, equal)) == NULL)
			ft_perror("minishell");
	}
	else if ((env = ft_strdup(arg)) == NULL)
		ft_perror("minishell");
	if ((new_lst = ft_lstnew(env)) == NULL)
		ft_perror("minishell");
	ft_lstadd_back(&g_env_lst, new_lst);
}

int			ft_export(char **args)
{
	t_list	*lst;
	int		status;

	if (*args == NULL)
		return (ft_declare());
	status = 0;
	while (*args)
	{
		if (!validate(&args, &status))
			continue;
		if ((lst = find_env(*args)) != NULL)
		{
			if (envcmp(lst->content, *args) == '=')
			{
				args++;
				continue;
			}
			update_env(*args);
		}
		else
			add_env(*args);
		args++;
	}
	return (status);
}
