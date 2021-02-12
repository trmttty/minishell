/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:46:03 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/13 00:23:05 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			envcmp(const char *env1, const char *env2)
{
	while (*env1 && *env1 != '=' && *env1 == *env2)
	{
		env1++;
		env2++;
	}
	if (*env2 == '+')
		env2++;
	if (*env1 == '\0' && *env2 == '=')
		return (0);
	return (*env1 - *env2);
}

void		sort_env_lst(void)
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

char		**create_env_vec(t_list *env_lst)
{
	char	**env_vec;
	int		size;
	int		i;

	size = ft_lstsize(env_lst);
	if ((env_vec = ft_calloc(size + 1, sizeof(char*))) == NULL)
		ft_perror("minishell");
	i = 0;
	while (i < size)
	{
		if ((env_vec[i] = ft_strdup(env_lst->content)) == NULL)
			ft_perror("minishell");
		i++;
		env_lst = env_lst->next;
	}
	env_vec[i] = NULL;
	return (env_vec);
}

int			set_question(char *name, int code)
{
	char	*s_code;
	char	*tmp;
	char	*env;
	char	**arg;

	if ((tmp = ft_strjoin(name, "=")) == NULL)
		ft_perror("minishell");
	if ((s_code = ft_itoa(code)) == NULL)
		ft_perror("minishell");
	if ((env = ft_strjoin(tmp, s_code)) == NULL)
		ft_perror("minishell");
	free(s_code);
	free(tmp);
	if ((arg = ft_calloc(2, sizeof(char*))) == NULL)
		ft_perror("minishell");
	arg[0] = env;
	arg[1] = NULL;
	ft_export_question(arg);
	free(env);
	free(arg);
	return (0);
}

int			ft_export_question(char **args)
{
	if (find_env("?="))
		update_env(*args);
	else
		add_env(*args);
	return (0);
}
